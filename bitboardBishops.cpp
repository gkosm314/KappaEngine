#include "bitboard.cpp" 

/*
		WARNING:	This class is still UNTESTED.

		SUGGESTION: 	Add whiteColor and blackColor as parameter in Moves function 
				and decide if i will include blocker or not in the attack set.
				Then use Move and Chessboard classes to toggle based on specific targetSquare.

		SUGGESTION 2:   Generate capture attack-sets independently by returning unionOfFirstBlockers AND opponentColor
*/

BitboardBishops::BitboardBishops(U64 dec): Bitboard(dec) {}

U64 BitboardBishops::bishopRays[4][64];

void BitboardBishops::initializeBishopRays() {
	/* 0:north-east
	*  1:north-west
	*  2:south-west
	*  3:south -east*/

	/*Each of the following initialized attacksets is one of the 2 main diagonials excluding one corner each time written in hex*/

	bishopRays[0][0]   =  0x8040201008040200;
	bishopRays[1][7]   =  0x102040810204000;
	bishopRays[2][63]  =  0x40201008040201;
	bishopRays[3][56]  =  0x2040810204080;

	for(int i = 1; i < 8; i++){
		bishopRays[0][i] = bishopRays[0][i-1]<<1 & Bitboard::notAFile;
		bishopRays[1][7-i] = bishopRays[1][7-i+1]>>1 & Bitboard::notHFile;
		bishopRays[2][63-i] = bishopRays[2][63-i+1]>>1 & Bitboard::notHFile;
		bishopRays[3][i] = bishopRays[3][i-1]<<1 & Bitboard::notAFile;
	}
	
	for (int file = 0; file < 8; file++) {
		for (int rank = 1; rank < 8; rank++) {
			int index = 8*rank+file;
			 bishopRays[0][index] = bishopRays[0][index-8] << 8  & fullBitboard;
			 bishopRays[1][index] = bishopRays[1][index-8] << 8  & fullBitboard;
		}
	}

	for (int file = 0; file < 8; file++) {
		for (int rank = 6; rank > -1; rank--) {
			int index = 8*rank+file;
			 bishopRays[2][index] = bishopRays[2][index+8] >> 8  & fullBitboard;
			 bishopRays[3][index] = bishopRays[3][index+8] >> 8  & fullBitboard;
		}
	}
}

Bitboard BitboardBishops::BishopMoves(int index, Bitboard occupiedBitboard) {
	if ((occupiedBitboard.getBitboard()&(1ULL << index)) == 0) throw std::out_of_range("No bishop lies in this index");

	initializeBishopRays(); //move to startup
	int firstBlocker;
	
	/*north-east attack-set*/
	U64 northEastAttacks;
	U64 maskedBlockers = occupiedBitboard.getBitboard() & bishopRays[0][index]; 
	if (maskedBlockers != 0) { 
		firstBlocker = bitwise::bitScanForward(maskedBlockers);   
		northEastAttacks = bishopRays[0][index] ^ bishopRays[0][firstBlocker];
	}
	else northEastAttacks = bishopRays[0][index];
	
	/*north-west attack-set*/
	U64 northWestAttacks;
	maskedBlockers = occupiedBitboard.getBitboard() & bishopRays[1][index];	
	if (maskedBlockers != 0) { 
		firstBlocker = bitwise::bitScanForward(maskedBlockers); 
		northWestAttacks = bishopRays[1][index] ^ bishopRays[1][firstBlocker];	
	}
	else northWestAttacks = bishopRays[1][index];

	/*south-west attack-set*/
	U64 southWestAttacks;
	maskedBlockers = occupiedBitboard.getBitboard() & bishopRays[2][index]; 
	if (maskedBlockers != 0) { 
		firstBlocker = bitwise::bitScanReverse(maskedBlockers);   
		southWestAttacks = bishopRays[2][index] ^ bishopRays[2][firstBlocker];
	}
	else southWestAttacks = bishopRays[2][index];	
	
	/*south-east attack-set*/
	U64 southEastAttacks;
	maskedBlockers = occupiedBitboard.getBitboard() & bishopRays[3][index];	
	if (maskedBlockers != 0) { 
		firstBlocker = bitwise::bitScanReverse(maskedBlockers);
		southEastAttacks = bishopRays[3][index] ^ bishopRays[3][firstBlocker]; 
	}
	else southEastAttacks = bishopRays[3][index]; 


	return Bitboard(northEastAttacks|northWestAttacks|southWestAttacks|southEastAttacks);	 
}

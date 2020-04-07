#include "bitboard.cpp" //??

BitboardRooks::BitboardRooks(U64 dec): Bitboard(dec) {}

U64 BitboardRooks::rookRays[4][64];

void BitboardRooks::initializeRookRays() {
	/* 0:east
	*  1:west
	*  2:north
	*  3:south */

    /*east & west rays*/
    U64 currentEast = Bitboard::firstRank;
	U64 currentWest = Bitboard::firstRank;
    for (int file = 0; file < 8; file++) {
		currentEast = (currentEast << 1) & Bitboard::notAFile;   
        currentWest = (currentWest >> 1) & Bitboard::notHFile;
		U64 tempEast = currentEast;
		U64 tempWest = currentWest;
        for (int rank = 0; rank < 8; rank++) { //fill the same file 
            int index = 8*rank+file;
            rookRays[0][index] = tempEast;          //8*rank+file
			rookRays[1][index-2*file+7] = tempWest; //8*rank+(7-file) = (8*rank+file)-2*file+7
            tempEast <<= 8; //shift "up"    
			tempWest <<= 8; 
		}
    }

	/*north & east rays*/
	U64 currentNorth = ~Bitboard::notAFile;
	U64 currentSouth = ~Bitboard::notAFile;
	for (int rank = 0; rank < 8; rank++) {
		currentNorth <<= 8;
		currentSouth >>= 8;
		U64 tempNorth = currentNorth;
		U64 tempSouth = currentSouth;
		for (int file = 0; file < 8; file++) {
			int index = 8*rank+file;
			rookRays[2][index] = tempNorth;
			rookRays[3][8*(7-rank)+file] = tempSouth; 
			tempNorth = (tempNorth << 1) & Bitboard::notAFile; //shift "right"
			tempSouth = (tempSouth << 1) & Bitboard::notAFile;
		}
	}	
}

Bitboard BitboardRooks::RookMoves(int index, Bitboard occupiedBitboard) {
	if ((occupiedBitboard.getBitboard()&(1ULL << index)) == 0) throw std::out_of_range("No rook lies in this index");

	initializeRookRays(); //move to startup
	int firstBlocker;
	
	/*east attack-set*/
	U64 eastAttacks;
	U64 maskedBlockers = occupiedBitboard.getBitboard() & rookRays[0][index]; 
	if (maskedBlockers != 0) { 
		firstBlocker = bitwise::bitScanForward(maskedBlockers);   
		eastAttacks = rookRays[0][index] ^ rookRays[0][firstBlocker];
	}
	else eastAttacks = rookRays[0][index];
	
	/*west attack-set*/
	U64 westAttacks;
	maskedBlockers = occupiedBitboard.getBitboard() & rookRays[1][index];	
	if (maskedBlockers != 0) { 
		firstBlocker = bitwise::bitScanReverse(maskedBlockers); 
		westAttacks = rookRays[1][index] ^ rookRays[1][firstBlocker];	
	}
	else westAttacks = rookRays[1][index];

	/*north attack-set*/
	U64 northAttacks;
	maskedBlockers = occupiedBitboard.getBitboard() & rookRays[2][index]; 
	if (maskedBlockers != 0) { 
		firstBlocker = bitwise::bitScanForward(maskedBlockers);   
		northAttacks = rookRays[2][index] ^ rookRays[2][firstBlocker];
	}
	else northAttacks = rookRays[2][index];	
	
	/*south attack-set*/
	U64 southAttacks;
	maskedBlockers = occupiedBitboard.getBitboard() & rookRays[3][index];	
	if (maskedBlockers != 0) { 
		firstBlocker = bitwise::bitScanReverse(maskedBlockers);
		southAttacks = rookRays[3][index] ^ rookRays[3][firstBlocker]; 
	}
	else southAttacks = rookRays[3][index]; 


	return Bitboard(eastAttacks|westAttacks|northAttacks|southAttacks);	 
}



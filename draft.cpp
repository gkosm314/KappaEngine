#include <iostream>

typedef unsigned long long int U64; 
#define C64(constantU64) constantU64##ULL 

class Bitboard {
	public:
		Bitboard(U64 bin): b(bin) {}
		int toList(int list[32]); //passed by ref? 
		friend std::ostream& operator<<(std::ostream &out, Bitboard board);
	protected: 
		U64 b;
		int bitScanForward();
};

int Bitboard::bitScanForward() {
	/** 
	 * returns the index of LSB between [0,63]
	 * adapted by CPW, original by @author Kim Walisch (2012)  
	 */
	if (!b) throw "empty bitboard";
    const int index64[64] = {
   		 0, 47,  1, 56, 48, 27,  2, 60,
   		57, 49, 41, 37, 28, 16,  3, 61,
		54, 58, 35, 52, 50, 42, 21, 44,
		38, 32, 29, 23, 17, 11,  4, 62,
		46, 55, 26, 59, 40, 36, 15, 53,
		34, 51, 20, 43, 31, 22, 10, 45,
		25, 39, 14, 33, 19, 30,  9, 24,
		13, 18,  8, 12,  7,  6,  5, 63
	};

    const U64 debruijn64 = C64(0x03f79d71b4cb0a89);
    return index64[((b ^ (b-1)) * debruijn64) >> 58];
}

int Bitboard::toList(int list[32]) {
	int size = 0;
	while (b) {
		list[size++] = bitScanForward(); //increment pointer and dereference old value (postfix)
		b &= b-1; //reset LSB 
	} 
	return size;
}

std::ostream& operator<<(std::ostream &out, Bitboard board) {
	for (int rank = 7; rank >= 0; rank--) {
		for (int file = 0; file < 8; file++) {
			int index = rank*8+file;
			if (board.b & (1ULL << index)) out << "1 "; 
			else out << "0 ";
		}
		out << "\n";
	}
	return out;
}


class Notation{
	Notation(); //constructor that accepts valid notations
	Notation(U64 bin); //second constructor
	int getNotationIndex(); //return index
	protected:
		int rank;
		char file;
		int notationIndex;
};
//class Move{};
class Chessboard{
	public:
		void reset();// make object equal to the starting state
		play()
	protected:
		Bitboard	whitePawns, //WRONG
					blackPawns,
					whiteRooks,
					blackRooks,
					whiteKnights,
					blackKnights,
					whiteBishops,
					blackBishops,
					whiteQueens,
					blackQueens,
					whiteKing,
					blackKing;
		bool sideToMove;			
}
class Game {

};

int main() {
	Chessboard test;
	test.reset();

	Notation currentMove;
	while(!Game.finished()) {

	}
	return 0;
}

// int main() {
// 	Bitboard mybitboard(1ULL<<63);
// 	std::cout << mybitboard << std::endl;
// }
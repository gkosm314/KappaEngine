#include "bitboard.hpp"

/*bitwise operations*/
namespace bitwise {

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

int bitScanForward(U64 bb) {
	/**
	 * returns the index of LSB between [0,63]
	 * adapted by CPW, original by @author Kim Walisch (2012)
	 */
	if (!bb) throw std::domain_error("Bitboard is empty");

    const U64 debruijn64 = C64(0x03f79d71b4cb0a89);
    return index64[((bb ^ (bb-1)) * debruijn64) >> 58];
}

int bitScanReverse(U64 bb) {
    /**
	 * returns the index of MSB between [0,63]
	 * adapted by CPW, original by @author Kim Walisch (2012)
	 */
    if (!bb) throw std::domain_error("Bitboard is empty");
   
    bb |= bb >> 1; 
    bb |= bb >> 2;
    bb |= bb >> 4;
    bb |= bb >> 8;
    bb |= bb >> 16;
    bb |= bb >> 32;
    const U64 debruijn64 = C64(0x03f79d71b4cb0a89);
    return index64[(bb * debruijn64) >> 58];
}


std::list<int> extractIndexes(U64 bb) {
    std::list<int> myList;
	while (bb) {
		myList.push_back(bitScanForward(bb));
		bb &= bb-1; //reset LSB
	}
	return myList;
}

void printBitboard(std::ostream &out, U64 bb){
    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 0; file < 8; file++) {
            int index = rank*8+file;
            if (bb & (1ULL << index)) out << "1 ";
                else out << "0 ";
        }
        out << "\n";
    }
}

} //namespace bitwise 


Bitboard::Bitboard(U64 dec) {
    bb = dec;
}

int Bitboard::bitScanForward() {
    return bitwise::bitScanForward(bb);
}

int Bitboard::bitScanReverse() {
    return bitwise::bitScanReverse(bb);
}

void Bitboard::printNumber() const {
    std::cout << bb;
    return;
}

std::ostream& operator<<(std::ostream &out, const Bitboard board){
    bitwise::printBitboard(out, board.bb);
    return out;
}

bool Bitboard::empty() const {
    return bb == 0;
}

Bitboard Bitboard::getComplement() const {
    return Bitboard(~bb);
}

void Bitboard::bitToggle(int index) {
    bb ^= (1ULL << index);
    return;
}

std::list<int> Bitboard::extractIndexes() const {
	return bitwise::extractIndexes(bb);
}

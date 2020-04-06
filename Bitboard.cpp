#include "bitboard.hpp"


Bitboard::Bitboard(U64 dec) {
    bb = dec;
}

int Bitboard::BitScanForward() {
	/**
	 * returns the index of LSB between [0,63]
	 * adapted by CPW, original by @author Kim Walisch (2012)
	 */
	if (!bb) throw empty_bitboard();
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
    return index64[((bb ^ (bb-1)) * debruijn64) >> 58];
}

void Bitboard::printNumber() const{
    std::cout << bb;
    return;
}

std::ostream& operator<<(std::ostream &out, const Bitboard board){
    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 0; file < 8; file++) {
            int index = rank*8+file;
            if (board.bb & (1ULL << index)) out << "1 ";
                else out << "0 ";
        }
        out << "\n";
    }
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
    return ;
}
std::list<int> Bitboard::extractIndexes() const {
    Bitboard temp = *this;
    std::list<int> myList;
	while (temp.bb) {
		myList.push_back(temp.BitScanForward());
		temp.bb &= temp.bb-1; //reset LSB
	}
	return myList;
}

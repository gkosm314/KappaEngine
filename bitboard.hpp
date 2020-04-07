#include <iostream>
#include <list>
#include <string>
#include <exception>

typedef unsigned long long int U64;
#define C64(constantU64) constantU64##ULL

class Bitboard {
    public:
        Bitboard(U64 dec); //decimal to bitboard
        std::list<int> extractIndexes() const;
        void bitToggle(int index); //index: 0-64 (maybe needs overload ?)
        Bitboard getComplement() const;
        U64 getBitboard() const{return bb;}
        friend std::ostream& operator<<(std::ostream &out, Bitboard bit); //prints as chessboard
        void printNumber() const;                                               //prints number
        bool empty() const;
        int BitScanForward();
    protected:
        U64 bb; //bitboard 64bit
        static const U64 notAFile = 0xfefefefefefefefe;
        static const U64 notHFile = 0x7f7f7f7f7f7f7f7f;
        static const U64 notABFile = 0xFCFCFCFCFCFCFCFC;
        static const U64 notGHFile = 0x3F3F3F3F3F3F3F3F;
        static const U64 firstRank = (1ULL << 8)-1;
        static const U64 secondRank =  (1ULL << 16)-1;
        static const U64 eighthRank =   (1ULL << 63)-1;
        class empty_bitboard : public std::exception {};
};

class BitboardPawns : public Bitboard { //protected or public ??
    public:
        BitboardPawns(U64 dec) : Bitboard(dec) {}
        virtual Bitboard generateLeftCaptures(const Bitboard &opponentColor) = 0;  //remember overflow mask
        virtual Bitboard generateRightCaptures(const Bitboard &opponentColor) = 0; //remember overflow mask
        virtual Bitboard generateFrontMoves(const Bitboard &unoccupied) = 0;
        virtual Bitboard generateDoubleFrontMoves(const Bitboard &unoccupied) = 0; //AND with second rank!!! -> push with generateFrontMoves() -> push again(avoid jumping)
};

class BitboardWhitePawns : public BitboardPawns {
    public:
        BitboardWhitePawns(U64 dec) : BitboardPawns(dec) {}
        Bitboard generateLeftCaptures(const Bitboard &opponentColor) ;  //remember overflow mask
        Bitboard generateRightCaptures(const Bitboard &opponentColor); //remember overflow mask
        Bitboard generateFrontMoves(const Bitboard &unoccupied);
        Bitboard generateDoubleFrontMoves(const Bitboard &unoccupied);

};

class BitboardBlackPawns : public BitboardPawns {
    public:
        BitboardBlackPawns(U64 dec) : BitboardPawns(dec) {}
        Bitboard generateLeftCaptures(const Bitboard &opponentColor) ;  //remember overflow mask
        Bitboard generateRightCaptures(const Bitboard &opponentColor); //remember overflow mask
        Bitboard generateFrontMoves(const Bitboard &unoccupied);
        Bitboard generateDoubleFrontMoves(const Bitboard &unoccupied);
};

class BitboardKnights : public Bitboard {
    public:
        BitboardKnights(U64 dec);
        Bitboard knightMoves(int knightIndex, const Bitboard &sameColor); //exception if index does not really correspond to Knight
        static void initialize();                 //may become global
    protected:
        static Bitboard precalculatedKnights[64]; //may become global
};

class BitboardRooks : public Bitboard {
    public:
        BitboardRooks(U64 dec);
        Bitboard RookMoves(int index, Bitboard occupiedBitboard); //check if we include last blocker

    protected:
        enum rookDirection {north, south, west, east}; //??
        static U64 rookRays[4][64]; //rays[direction][index]  -  possible moves when chessboard is empty
        void static initializeRookRays(); //TODO static or not ?
};

class BitboardBishops : public Bitboard {
    public:
        BitboardBishops(U64 dec);
        Bitboard BishopMoves(int index, Bitboard occupiedBitboard); //check if we include last blocker
    protected:
        enum bishopDirection {northWest, southWest, northEast, southEast}; //??
        static U64 bishopRays[4][64]; //rays[direction][index]  -  possible moves when chessboard is empty
};

class BitboardQueens : public BitboardRooks, public BitboardBishops {
    public:
        Bitboard QueenMoves(); //union BishopMoves and RookMoves
};

class BitboardKing : public Bitboard{
    public:
        Bitboard KingMoves();
};

class Move {
    public:
        Move(int start, int end, bool capture, bool spmove, bool dpmove) : startIndex(start), endIndex(end), isCapture(capture), isSinglePawnMove(spmove),isDoublePawnMove(dpmove){};
    private:
        int startIndex, endIndex;
        bool isCapture;
        bool isSinglePawnMove; //useful for promotions
        bool isDoublePawnMove;
};

class Chessboard { // :)
    public:
        Chessboard(Chessboard current, Move next);
        Chessboard(); //initialize chessboard with starting position (hard-coded)
        Chessboard(std::string fen);
        std::list<Move> getMoves(); //dont forget castling, legal check
    private:
        Bitboard allWhite, allBlack;
        BitboardWhitePawns whitePawns;
        BitboardBlackPawns blackPawns;
        BitboardKnights whiteKnights, blackKnights;
        BitboardBishops whiteBishops, blackBishops;
        BitboardRooks whiteRooks, blackRooks;
        BitboardQueens whiteQueens, blackQueens;
        BitboardKing whiteKing, blackKing;
        Bitboard occupied, unoccupied;
        bool whiteCastlingLeft, whiteCastlingRight, blackCastlingLeft, blackCastlingRight;
        bool whitesTurn;
};

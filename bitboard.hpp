#include <iostream>
#include <list>
#include <string>

typedef unsigned long long int U64;  
#define C64(constantU64) constantU64##ULL 

class Bitboard {
    public: 
        Bitboard(U64 dec); //decimal to bitboard
        std::list<int> extractIndexes();
        void bitToggle(int index); //index: 0-64 (maybe needs overload ?)
        Bitboard getComplement();
        U64 getBitboard() {return bb;}
        friend std::ostream& operator<<(std::ostream &out, Bitboard bit); //prints as chessboard
        void printNumber();                                               //prints number
        bool empty();
    protected:
        U64 bb; //bitboard 64bit
        int BitScanForward();
};

class BitboardPawns : public Bitboard { //protected or public ??
    public:
        Bitboard generateLeftCaptures();  //remember overflow mask 
        Bitboard generateRightCaptures(); //remember overflow mask 
        Bitboard generateFrontMoves();
        Bitboard generateDoubleFrontMoves(); //AND with second rank!!! -> push with generateFrontMoves() -> push again(avoid jumping)
        Bitboard generateEnPassant(Bitboard PreviousDoubleFrontMoves);      
            //shift PreviousDoubleFrontMoves eight back = bitboard A
            //generate left and right captures
            //exclude already produced captures (by logical AND with the bitboard A)
       
        
        //promotions
};  

class BitboardKnights : public Bitboard { 
    public:
        Bitboard knightMoves(int index); //exception if index does not really correspond to Knight
        static void initialize();                 //may become global
    protected: 
        static Bitboard precalculatedKnights[64]; //may become global       
};

class BitboardRooks : public Bitboard {
    public:
        Bitboard RookMoves(int index, Bitboard occupiedBitboard); //check if we include last blocker
    protected:
        enum rookDirection {north, south, west, east}; //??
        U64 rookRays[4][64]; //rays[direction][index]  -  possible moves when chessboard is empty
};

class BitboardBishops : public Bitboard {
    public:
        Bitboard BishopMoves(int index, Bitboard occupiedBitboard); //check if we include last blocker
    protected:
        enum bishopDirection {northWest, southWest, northEast, southEast}; //??
        U64 bishopRays[4][64]; //rays[direction][index]  -  possible moves when chessboard is empty    
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
        Move(int start, int end, bool capture) : startIndex(start), endIndex(end), isCapture(capture) {};
    private:
        int startIndex, endIndex;
        bool isCapture;
};

class Chessboard { // :)
    public:
        Chessboard(Chessboard current, Move next);
        Chessboard(); //initialize chessboard with starting position (hard-coded)
        Chessboard(std::string fen);
        std::list<Move> getMoves(); //dont forget castling, legal check
    private:
        Bitboard allWhite, allBlack;
        BitboardPawns whitePawns, blackPawns;
        BitboardKnights whiteKnights, blackKnights;
        BitboardBishops whiteBishops, blackBishops;
        BitboardRooks whiteRooks, blackRooks;
        BitboardQueens whiteQueens, blackQueens;
        BitboardKing whiteKing, blackKing;
        Bitboard occupied, unoccupied;
        bool whiteCastlingLeft, whiteCastlingRight, blackCastlingLeft, blackCastlingRight;
};
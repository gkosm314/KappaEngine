class Bitboard{
	protected:
		unsigned long long int b;
};

class Chessboard{
	public:
	protected:
		Bitboard 	whitePawns,
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

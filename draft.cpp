class Bitboard{
	public:

	protected: 
		unsigned long long int b;
};
class Notation{
	Notation(); //constructor that accepts valid notations
	Notation(unsigned long long int bin); //second constructor
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
		Bitboard	whitePawns,
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
class Game{

};

int main(){
	Chessboard test;
	test.reset();

	Notation currentMove;
	while(!Game.finished()){

	}
	return 0;
}
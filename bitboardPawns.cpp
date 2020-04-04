#include "bitboard.hpp"
/*        
            ->Captures don't check legality
            ->Captures don't toggle previous position
            ->Captures don't toggle opponent's position's
            ->En passant is one move, so it doesn't need to be stored in a bitboard
            ->Maybe we should merge BitboardWhitePawns and BitboardBlackPawns using a condition inside BitboardPawns
*/
Bitboard BitboardWhitePawns::generateLeftCaptures(const Bitboard &opponentColor) {
    return Bitboard( (bb << 7) & notHFile &opponentColor.getBitboard());
}
Bitboard BitboardWhitePawns::generateRightCaptures(const Bitboard &opponentColor) {
    return Bitboard( (bb << 9) & notAFile & opponentColor.getBitboard());
}
Bitboard BitboardWhitePawns::generateFrontMoves(const Bitboard &unoccupied) {
    return  Bitboard( (bb << 8) & unoccupied.getBitboard());
}
Bitboard BitboardWhitePawns::generateDoubleFrontMoves(const Bitboard &unoccupied){
    return (((((bb & secondRank) << 8) & unoccupied.getBitboard()) << 8) & unoccupied.getBitboard());
}

Bitboard BitboardBlackPawns::generateLeftCaptures(const Bitboard &opponentColor) {
    return Bitboard( (bb >> 7) & notAFile &opponentColor.getBitboard());
}
Bitboard BitboardBlackPawns::generateRightCaptures(const Bitboard &opponentColor) {
    return Bitboard( (bb >> 9) & notHFile & opponentColor.getBitboard());
}
Bitboard BitboardBlackPawns::generateFrontMoves(const Bitboard &unoccupied) {
    return  Bitboard( (bb >> 8) & unoccupied.getBitboard());
}
Bitboard BitboardBlackPawns::generateDoubleFrontMoves(const Bitboard &unoccupied){
    return Bitboard(((((bb & eighthRank) >> 8) & unoccupied.getBitboard()) >> 8) & unoccupied.getBitboard());
}
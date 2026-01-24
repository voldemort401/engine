#ifndef BOARD_HPP
#define BOARD_HPP
#include <string>

#define BLACK 0
#define WHITE 1

// ERROR CODES
#define ENGINE_OK 2
#define ENGINE_FEN_ERR 3
#define ENGINE_UNKWN_ERR 4
#define ENGINE_INVALID_SQUARE 5

#define ENGINE_STALEMATE 6
#define ENGINE_CHECKMATE 7
#define ENGINE_INSUFFICIENT_MATERIAL 8
#define ENGINE_50MOVERULE 9

typedef unsigned long long piece;

inline piece whiteKing;
inline piece whiteQueen;
inline piece whiteKnight;
inline piece whitePawn;
inline piece whiteBishop;
inline piece whiteRook;

inline piece blackKing;
inline piece blackQueen;
inline piece blackKnight;
inline piece blackPawn;
inline piece blackBishop;
inline piece blackRook;

inline piece enPassantSquare;

inline bool kwhiteCastle;
inline bool qwhiteCastle;
inline bool kblackCastle;
inline bool qblackCastle;

inline int turn;
inline int halfmoveClock;
inline int fullmoveClock;

inline bool blackKingSideCastle;
inline bool blackQueenSideCastle;
inline bool whiteKingSideCastle;
inline bool whiteQueenSideCastle;

struct movement
{
  const int king(piece square);
  const int queen(piece square);
  const int pawn(piece square);
  const int bishop(piece square);
  const int knight(piece square);
  const int rook(piece square);
};

/*
   from the supplied fen sets the whiteKing, blackKing, turn,etc to the required values
   returns ENGINE_OK on success and ENGINE_FEN_ERR || ENGINE_UNKWN_ERR on faliure
*/
const int Setpos(std::string fen);

/*
   takes any square in the chess board in the form of 'e3' or 'e4' and
   returns the bitboard associated with the square on success and 
   returns either ENGINE_INVALID_SQUARE or ENGINE_UNKWN_ERR on faliure
*/
piece s2s(std::string square);

/*
   either returns ENGINE_STALEMATE ENGINE_CHECKMATE ENGINE_INSUFFICIENT_MATERIAL ENGINE_50MOVERULE
*/
const int gameOver();


#endif /* ifndef BOARD_HPP */

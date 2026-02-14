#ifndef BOARD_HPP
#define BOARD_HPP
#include <string>

#define ENGINE_OK                     0xE1  
#define ENGINE_FEN_ERR                0xE2  
#define ENGINE_UNKWN_ERR              0xE3  
#define ENGINE_INVALID_SQUARE         0xE4  
#define ENGINE_STALEMATE              0xE5  
#define ENGINE_CHECKMATE              0xE6  
#define ENGINE_INSUFFICIENT_MATERIAL  0xE7  
#define ENGINE_50MOVERULE             0xE8  

#define RANKS                         0x8
#define FILES                         0x8
#define BLACK                         0x0   
#define WHITE                         0x1   
#define KING_MAX_MOVES                0x8   

// Bit manupulation
#define set_bit(bitboard, square) (bitboard ^= (1ULL<<square))

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
piece to_bitboard(std::string square);

/* 
 * take a 64 bit unsigned integer square as its input and returns the corresponding 
 * notation for that square.
 *
 * NOTE: the argument "square" need to have only one bit set as 1 otherwise 
 * it will return ENGINE_INVALID_SQUARE 
 */ 
std::string to_standardNOT(piece square);

/*
   either returns ENGINE_STALEMATE ENGINE_CHECKMATE ENGINE_INSUFFICIENT_MATERIAL ENGINE_50MOVERULE
*/
const int gameOver();


#endif /* ifndef BOARD_HPP */

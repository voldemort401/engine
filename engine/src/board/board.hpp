#ifndef BOARD_HPP
#define BOARD_HPP
#include <cstdint>
#include <string>

typedef uint64_t U64;
namespace errors
{
  inline constexpr uint8_t ENGINE_OK                    = 0xE1;
  inline constexpr uint8_t ENGINE_FEN_ERR               = 0xE2;
  inline constexpr uint8_t ENGINE_UNKWN_ERR             = 0xE3;
  inline constexpr uint8_t ENGINE_INVALID_SQUARE        = 0xE4;
  inline constexpr uint8_t ENGINE_INVALID_PIECE         = 0xE9;
}

namespace game_overs
{
  inline constexpr uint8_t ENGINE_STALEMATE             = 0xE5;
  inline constexpr uint8_t ENGINE_CHECKMATE             = 0xE6;
  inline constexpr uint8_t ENGINE_INSUFFICIENT_MATERIAL = 0xE7;
  inline constexpr uint8_t ENGINE_50MOVERULE            = 0xE8;
}

namespace constants 
{
  inline constexpr U64 RANK_1 =    0xFF00000000000000;
  inline constexpr U64 RANK_8 =    0xFF;
  inline constexpr U64 H_FILE =    0x8080808080808080;
  inline constexpr U64 A_FILE =    0x101010101010101;
  inline constexpr uint8_t BLACK  =0x0;
  inline constexpr uint8_t WHITE  =0x1;
}


/*BIT MANIPULATION MACROS
 *THE POSITION VARIABLE MUS BE BETWEEN 0 AND 63 THE RESULT WILL
 *BE UNDEFINED OTHERWISE*/

#define set_bit(bit, position)       (bit ^= (1ULL<<position))
#define get_rank(bitboard_of_square) (to_standardNOT(square)[1] - '0')
#define read_bit(position, variable) ((1ULL << position) & variable)


inline U64 whiteKing;
inline U64 whiteQueen;
inline U64 whiteKnight;
inline U64 whitePawn;
inline U64 whiteBishop;
inline U64 whiteRook;

inline U64 blackKing;
inline U64 blackQueen;
inline U64 blackKnight;
inline U64 blackPawn;
inline U64 blackBishop;
inline U64 blackRook;

inline U64 previousMove;

inline U64 whiteBlockers;
inline U64 blackBlockers;

inline uint32_t extra_vars;

struct movement
{
  U64 king(U64 square);
  U64 queen(U64 square);
  U64 pawn(U64 square, int color);

  U64 bishop(U64 square, U64 blockers);
  U64 knight(U64 square, U64 blockers);
  U64 rook(U64 square, U64 blockers);
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
U64 to_bitboard(std::string square, bool decimal = false);

/*
 * take a 64 bit unsigned integer square as its input and returns the corresponding
 * notation for that square.
 *
 * NOTE: the argument "square" need to have only one bit set as 1 otherwise
 * it will return ENGINE_INVALID_SQUARE
 */
std::string to_standardNOT(U64 square);

/*
   either returns ENGINE_STALEMATE ENGINE_CHECKMATE ENGINE_INSUFFICIENT_MATERIAL ENGINE_50MOVERULE
   */
const int gameOver();

bool in_check();

#endif /* ifndef BOARD_HPP */

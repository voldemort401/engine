#include "board.hpp"
#include <iostream>
#include <bitset>
#include <sstream>
#include <stdexcept>
#include <string>
#include <map>

std::string to_standardNOT(piece __piece)
{
  std::string notation = ""; 
  int current_square = __builtin_ctzll(__piece); 

  int rank = 7 - (current_square/8);
  int file = (current_square + rank*8) - 56;

  char _rank = rank + '1';
  char _file = file + 'a'; 

  notation += _file;
  notation += _rank;

  return notation; 
}

piece to_bitboard(std::string square, bool decimal)
{
  if (square.length() != 2){
    return ENGINE_INVALID_SQUARE;
  }

  int file = square[0]; // int file will store the ascii value of the file 
  int rank = square[1] - '0'; 

  if (rank > 8)
  {
    return ENGINE_INVALID_SQUARE;
  }
  // 0x61(97) and 0x68(104) are the ascii values of a and h respectively
  if (file > 'h' || file < 'a')
  {
    return ENGINE_INVALID_SQUARE;
  }

  file = file-'`';
  int _square = (63-(8-file) - (rank-1)*8);
  if (decimal == false)
  {
    piece sq = (unsigned long long)1 << _square; 
    return sq;
  }
  else{
    return _square;
  }
  return ENGINE_UNKWN_ERR;  
}

const int Setpos(std::string fen){
  previousMove = 0;
  if (fen.length() == 0){
    return ENGINE_FEN_ERR;
  }

  /*
     we are bascially seperating the fen into 2 different variables for eg:

     for the input of fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
     pieces_pos will be equal to "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"
     and extra_bits will be equal to "w KQkq - 0 1"
     */

  std::string pieces_pos;
  std::string extra_bits;

  /*
     for some reason it returns 18446744073709551615% when it cant find the char in the string and
     since the largest possible fen for normal chess is 90
     */

  if (fen.find(" w") > 90){
    turn = BLACK;
    pieces_pos = fen.substr(0, fen.find(" b"));
    extra_bits = fen.substr(fen.find(" b"), fen.length());
  }

  else if (fen.find(" b") > 90)
  {
    turn = WHITE;
    pieces_pos = fen.substr(0, fen.find(" w"));
    extra_bits = fen.substr(fen.find(" w"), fen.length());
  }

  else{
    return ENGINE_FEN_ERR;
  }
  std::string cpiece;
  /*
     we are starting the value of csquare with -1 cause when we first add the csquare by 1
     we want to start from 0.
     we want to start from 0 because it helps to prevent a bug when the csquare value is 64
     and if we leftshift by 64 like this (mask << 64) the 1 gets lost somewhere so we need to leftshift
     by 63 instead.
     */
  int csquare{-1};

  /*
Uppercase: white pieces
Lowercase: black pieces
*/

  std::map<std::string, int> pieces;
  pieces = {{"r", 1},{"n", 2},{"b", 3},{"q", 4},{"k", 5},{"p", 6},
    {"R", 7},{"N", 8},{"B", 9},{"Q", 10},{"K", 11},{"P", 12}};


  // half move and full move clock
  std::stringstream extra_bit_stream(extra_bits);
  // we are using this var temp because it jst makes it easier to read for me
  int temp, itr{0};
  for (std::string info; std::getline(extra_bit_stream, info, ' ');)
  {
    if (itr > 5)
    {
      return ENGINE_FEN_ERR;
    }
    // temp throws a std::invalid_argument if the provided string cant be converted to a number
    try{
      temp = std::stoi(info);
    }
    catch (std::invalid_argument){
      temp = -1;
      if (info != "w" && info != "b")
      {
        // castling rights
        if (itr == 2)
        {
          for (int i = 0; i<info.length();i++)
          {
            cpiece = info[i];
            switch (pieces[cpiece])
            {
              case 5:
                blackKingSideCastle = true;
                break;
              case 11:
                whiteKingSideCastle = true;
                break;

              case 4:
                blackQueenSideCastle = true;
                break;

              case 10:
                whiteQueenSideCastle = true;
                break;

              default:
                return ENGINE_FEN_ERR;
                break;
            }
          }
        }

        //enpassant square
        else if (itr == 3 && info != "-")
        {
          enPassantSquare = to_bitboard(info);
          if (enPassantSquare == ENGINE_INVALID_SQUARE)
          {
            return ENGINE_FEN_ERR;
          }
        };

      }
    };

    /*
       at the end of a fen the fen always has a structure like
       "w KQkq enpassant_squares fullmoveclock halfmoveclock" notice how fullmoveclock is
       after 3 pieces of information or in the 4th pos so if when the program is supposed to be
       pointing at fullmoveclock if we cant convert to a number then the fen would be invalid
       */
    if (itr == 4 && temp == -1)
    {
      return ENGINE_FEN_ERR;
    }
    else if (itr == 4 && temp != -1)
    {
      fullmoveClock = temp;
    };


    if (itr == 5 && temp == -1)
    {
      return ENGINE_FEN_ERR;
    }
    else if (itr == 5 && temp != -1)
    {
      halfmoveClock = temp;
    };

    itr+=1;
  }


  for (int i = 0; i<pieces_pos.length(); i++){
    cpiece = pieces_pos[i];
    csquare+=1;

    if (pieces[cpiece] != 0 ){
      if (pieces[cpiece] <= 6)
      {
        switch (pieces[cpiece])
        {
          case 1:
            set_bit(blackRook, csquare);
            break;
          case 2:
            set_bit(blackKnight, csquare);
            break;
          case 3:
            set_bit(blackBishop, csquare);
            break;
          case 4:
            set_bit(blackQueen, csquare);
            break;
          case 5:
            set_bit(blackKing, csquare);
            break;
          case 6:
            set_bit(blackPawn, csquare);
            break;

          default:
            return ENGINE_UNKWN_ERR;
            break;
        }
      }

      else
      {
        switch (pieces[cpiece])
        {
          case 7:
            set_bit( whiteRook, csquare);
            break;
          case 8:
            set_bit(whiteKnight, csquare);
            break;
          case 9:
            set_bit(whiteBishop, csquare);
            break;
          case 10:
            set_bit( whiteQueen, csquare);
            break;
          case 11:
            set_bit(whiteKing, csquare);
            break;
          case 12:
            set_bit(whitePawn, csquare);
            break;

          default:
            return ENGINE_UNKWN_ERR;
            break;
        }

      }

    }
    else if (cpiece == "/")
    {
      /*
         at the start of every iteration of this loop
         we add the csquare var by 1 but if the current
         "piece" we are at is just a "/" then we subtract
         csquare.
         */
      csquare -= 1;
    }

    else if (std::isdigit(pieces_pos[i]))
    {
      /*
         (int)(piece_pos[i]) gives us the ascii value for the char for eg
         (int)("8") wont give 8 but instead give 56 as 56 is the ascii for "8"
         so if we subtract 42 from 56 we get 8. so by subtracting 42 from the ascii
         value of a digit we can get the digit. we subtract by another 1 because 1 was already
         added to csquare at the start of the iteration
         */
      csquare += (int)(pieces_pos[i])-49;
    }

    else
    {
      return ENGINE_FEN_ERR;
    };
  }

  return ENGINE_OK;
}

unsigned long long movement::pawn(piece square)
{
  piece illegal_squares, attack_squares; 
  int rank = get_rank(square);
  int starting_rnk, dposition{__builtin_ctzll(square)};
  std::bitset<64> _moves{0};

  if ((square & whitePawn) == 0 && (square & blackPawn) == 0)
  {
    return ENGINE_INVALID_PIECE;  
  }

  // BLACK PAWN
  if ( (square & whitePawn) == 0){
    attack_squares = whitePawn | whiteRook | whiteBishop | whiteKing | whiteQueen | whiteKnight; 
    illegal_squares = blackPawn | blackRook | blackBishop | blackKing | blackQueen | blackKnight; 

    starting_rnk = 7;
    /* --- VERTICAL MOVEMENT --- */
    if (rank == starting_rnk) 
    {
      for (int i = 1; i <=2; i++)
      {
        _moves.set(dposition+(i*8),1);
        /*converting bitset to ullong because can't really do bitwise operations with a type bitset and a type ullong*/
        if ((_moves.to_ullong() & illegal_squares) != 0 || (_moves.to_ullong() & attack_squares) != 0)
        {
          _moves.set(dposition+(i*8), 0);
          break; 
        }
      }
    }
    else 
    {
      _moves.set(dposition+8, 1);
      if ((_moves.to_ullong() & illegal_squares) != 0 || (_moves.to_ullong() & attack_squares) != 0)
      {
        _moves.set(dposition+8, 0);
      }
    }


    /*--- DIAGONAL MOVEMENTS ---*/
    /*NW OFFSET: +7
      NE OFFSET: +9*/ 

    if (dposition+7 <= 63 && (1ULL << (dposition+7) & attack_squares) != 0 && dposition % 8 != 0)
    {
      _moves.set(dposition+7,1);
    }

    if (dposition+9 <= 63 && (1ULL << (dposition+9) & attack_squares) != 0 && dposition % 8 != 7)
    {
      _moves.set(dposition+9,1);
    }

    /* --- ENPASSANT --- */ 
    if (enPassantSquare != 0 && enPassantSquare != ENGINE_INVALID_SQUARE)
    {
      if (dposition+9 >= 0 && enPassantSquare == (1ULL << (dposition+9)) && dposition%8 != 0)
      {
        _moves.set(__builtin_ctzll(enPassantSquare), 1);
      }

      if (dposition+7 >=0 && enPassantSquare == (1ULL<<(dposition+7)) && dposition%8 != 7)
      {
        _moves.set(__builtin_ctzll(enPassantSquare), 1);
      }
    }

    else if (previousMove != 0)
    {
      if (rank == 4 && _moves.test(dposition+7) != 1 && dposition % 8 != 7)
      {
        if ( (1ULL << (dposition-1) & whitePawn) != 0)
        {
          if ((previousMove & whitePawn) != 0 && read_bit( ((dposition-1) + (2*8)), previousMove) == 1)
          {
            _moves.set(dposition+7, 1);
          }
        } 
      } 

      if (rank == 4 && _moves.test(dposition+9) != 1 && dposition % 8 != 0)
      {
        if ( (1ULL << (dposition+1) & whitePawn) != 0)
        {
          if ((previousMove & whitePawn) != 0 && read_bit( ((dposition+1) + (2*8)), previousMove) == 1)
          {
            _moves.set(dposition+9, 1);
          }
        } 
      }
    }
  }

  // WHITE PAWN 
  else
  {
    illegal_squares = whitePawn | whiteRook | whiteBishop | whiteKing | whiteQueen | whiteKnight; 
    attack_squares  = blackPawn | blackRook | blackBishop | blackKing | blackQueen | blackKnight; 

    starting_rnk = 2;
    /* --- VERTICAL MOVEMENT --- */
    if (rank == starting_rnk) 
    {
      for (int i = 1; i <=2; i++)
      {
        _moves.set(dposition-(i*8),1);
        /*converting bitset to ullong because can't really do bitwise operations with a type bitset and a type ullong*/
        if ((_moves.to_ullong() & illegal_squares) != 0 || (_moves.to_ullong() & attack_squares) != 0)
        {
          _moves.set(dposition-(i*8), 0);
          break; 
        }
      }
    }
    else 
    {
      _moves.set(dposition-8, 1);
      if ((_moves.to_ullong() & illegal_squares) != 0 || (_moves.to_ullong() & attack_squares) != 0)
      {
        _moves.set(dposition-8, 0);
      }
    }


    /*--- DIAGONAL MOVEMENTS ---*/
    /*NW OFFSET: -7
      NE OFFSET: -9*/ 

    if (dposition-7 >= 0 && (1ULL << (dposition-7) & attack_squares) != 0 && dposition % 8 != 7)
    {
      _moves.set(dposition-7,1);
    }

    if (dposition-9 >= 0 && (1ULL << (dposition-9) & attack_squares) != 0 && dposition % 8 != 0)
    {
      _moves.set(dposition-9,1);
    }

    /* --- ENPASSANT --- */ 
    if (enPassantSquare != 0 && enPassantSquare != ENGINE_INVALID_SQUARE)
    {
      if (dposition-9 >= 0 && enPassantSquare == (1ULL << (dposition-9)) && dposition%8 != 0)
      {
        _moves.set(__builtin_ctzll(enPassantSquare), 1);
      }

      if (dposition-7 >=0 && enPassantSquare == (1ULL<<(dposition-7)) && dposition%8 != 7)
      {
        _moves.set(__builtin_ctzll(enPassantSquare), 1);
      }
    }

    else if (previousMove != 0)
    {
      if (rank == 5 && _moves.test(dposition-7) != 1 && dposition % 8 != 7)
      {
        if ( (1ULL << (dposition+1) & blackPawn) != 0)
        {
          if ((previousMove & blackPawn) != 0 && read_bit( ((dposition+1) - (2*8)), previousMove) == 1)
          {
            _moves.set(dposition-7, 1);
          }
        } 
      } 

      if (rank == 5 && _moves.test(dposition-9) != 1 && dposition % 8 != 0)
      {
        if ( (1ULL << (dposition-1) & blackPawn) != 0)
        {
          if ((previousMove & blackPawn) != 0 && read_bit( ((dposition-1) - (2*8)), previousMove) == 1)
          {
            _moves.set(dposition-9, 1);
          }
        } 
      }
    }
  }

  return _moves.to_ullong();
}

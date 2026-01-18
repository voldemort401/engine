#include <cctype>
#include <iostream>
#include "board.hpp"
#include <stdexcept>
#include <string>
#include <map>

const int Setpos(std::string fen){
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
  piece mask;

  /*
  Uppercase: white pieces
  Lowercase: black pieces
  */

  std::map<std::string, int> pieces;
  pieces = {{"r", 1},{"n", 2},{"b", 3},{"q", 4},{"k", 5},{"p", 6},
    {"R", 7},{"N", 8},{"B", 9},{"Q", 10},{"K", 11},{"P", 12}};

  for (int i = 0; i<=pieces_pos.length(); i++){
    cpiece = pieces_pos[i];
    csquare+=1;

    if (pieces[cpiece] != 0 ){
      if (pieces[cpiece] <= 6)
      {
        switch (pieces[cpiece])
        {
          case 1:
            mask = (unsigned long long)1 << csquare;
            blackRook ^= mask;
            break;
          case 2:
            mask = (unsigned long long)1 << csquare;
            blackKnight ^= mask;
            break;
          case 3:
            mask = (unsigned long long)1 << csquare;
            blackBishop ^= mask;
            break;
          case 4:
            mask = (unsigned long long)1 << csquare;
            blackQueen ^= mask;
            break;
          case 5:
            mask = (unsigned long long)1 << csquare;
            blackKing ^= mask;
            break;
          case 6:
            mask = (unsigned long long)1 << csquare;
            blackPawn ^= mask;
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
            mask = (unsigned long long)1 << csquare;
            whiteRook ^= mask;
            break;
          case 8:
            mask = (unsigned long long)1 << csquare;
            whiteKnight ^= mask;
            break;
          case 9:
            mask = (unsigned long long)1 << csquare;
            whiteBishop ^= mask;
            break;
          case 10:
            mask = (unsigned long long)1 << csquare ;
            whiteQueen ^= mask;
            break;
          case 11:
            mask = (unsigned long long)1 << csquare;
            whiteKing ^= mask;
            break;
          case 12:
            mask = (unsigned long long)1 << csquare;
            whitePawn ^= mask;
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

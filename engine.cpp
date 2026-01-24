#include "engine/src/board/board.hpp"
#include <iostream>

int main(){
  Setpos("rnbqkbnr/pppppppp/8/8/8/8/PPPPPP2/RNBQKBNR w KQkq - 0 1");
  movement movement;
  std::cout<<movement.king(whiteKing)<<'\n'; 
  return 0;
}

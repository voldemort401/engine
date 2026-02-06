#include "engine/src/board/board.hpp"
#include <iostream>
// a simple console visualizer
void printBitboardLabeled(piece bb) {
    std::cout << "  a b c d e f g h\n";
    for (int rank = 7; rank >= 0; rank--) {
        std::cout << rank + 1 << " ";
        for (int file = 0; file < 8; file++) {
            int square = rank * 8 + file;
            std::cout << (((bb >> square) & 1ULL) ? "1 " : ". ");
        }
        std::cout << rank + 1 << '\n';
    }
    std::cout << "  a b c d e f g h\n\n";
}

int main(){
  Setpos("rnbqkbnr/pppppppp/8/8/8/8/PPPPPP2/RNBQKBNR w KQkq - 0 1");
  movement movement;
  printBitboardLabeled(movement.king(whiteKing));
  std::cout<<movement.king(whiteKing);
  return 0;
}

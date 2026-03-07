#include "engine/src/board/board.hpp"
#include <chrono>
#include <bitset>
#include <iostream>

// a simple console visualizer
void printBitboard(uint64_t bitboard) {
    std::cout << "  a b c d e f g h" << std::endl;
    for (int rank = 0; rank < 8; ++rank) {
        std::cout << (8 - rank) << " "; // Print rank number (8 to 1)
        for (int file = 0; file < 8; ++file) {
            // Calculate the bit index (0-63)
            int square = rank * 8 + file;
            
            // Check if the bit at 'square' is set
            // We use 1ULL to ensure we are working with 64-bit integers
            if ((bitboard >> square) & 1ULL) {
                std::cout << "X ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main(){
  Setpos("rnbqkbnr/pppppppp/8/8/6P1/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
  piece whitePieces = whiteKnight | whiteKing | whiteRook | whiteBishop | whitePawn | whiteQueen;
//  std::bitset<64> w(whitePawn);
//  std::cout<<w<<'\n';
  movement movement;
  printBitboard(movement.pawn(274877906944ULL));

//  printBitboard(whitePieces);
//  printBitboard(1099511627776ULL);
  //1000000000000000000000000000000000000000000000000000000000000000 
  //std::cout<<movement.pawn(35460323737600ULL)<<'\n';

  auto start = std::chrono::high_resolution_clock::now();
  
  movement.pawn(274877906944ULL);   // function you want to measure
  
  auto end = std::chrono::high_resolution_clock::now();
  
  auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
  
  std::cout << "Time: " << duration.count() << " ns\n";
  return 0;
}

#include "../../engine/src/board/board.hpp"
#include <bitset>
#include <string>
#include <iostream>
   
class test {
  public:
    void test_to_bitboard();
    void test_to_standardNOT();
    void test_Setpos();
    void test_gameOver();
};

void test::test_to_bitboard(){
  piece result;
  std::string square1{"e1"}; 
  std::string square2{"h8"}; 
  std::string square3{"20e"}; 
  std::string square4{"e10"}; 

  result = to_bitboard(square4);
  if (result != ENGINE_INVALID_SQUARE){
    std::cout << "\033[31m" << "❌ Failed at "<< square4 << '\n';
    std::cout << "Expected:"<<ENGINE_INVALID_SQUARE<<" Got:"<<result << "\033[0m"<<'\n';
  }

  result = to_bitboard(square3);
  if (result != ENGINE_INVALID_SQUARE){
    std::cout << "\033[31m" << "❌ Failed at "<< square3 << '\n';
    std::cout << "Expected:"<<ENGINE_INVALID_SQUARE<<" Got:"<<result << "\033[0m"<<'\n';
  }

  result = to_bitboard(square2);
  if (result != 128){
    std::bitset<64> expected(64);
    std::bitset<64> got(result);

    std::cout << "\033[31m" << "❌ Failed at "<< square2 << '\n';
    std::cout << "Expected:"<<expected<<" Got:"<<got<< "\033[0m"<<'\n';
  }

  result = to_bitboard(square1);
  if (result != 1152921504606846976){
    std::bitset<64>expected(1152921504606846976); 
    std::bitset<64>got(result);

    std::cout << "\033[31m" << "❌ Failed at "<< square1 << '\n';
    std::cout << "Expected:"<<expected<<" Got:"<<got<< "\033[0m"<<'\n';
  }

};

int main(){
  test test; 
  test.test_to_bitboard();
};

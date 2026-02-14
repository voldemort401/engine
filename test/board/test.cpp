#include "../../engine/src/board/board.hpp"
#include <bitset>
#include <cmath>
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
  std::string square; 

  square = "20e";
  result = to_bitboard(square);
  if (result != ENGINE_INVALID_SQUARE){
    std::cout << "\033[31m" << "❌ Failed at "<< square << '\n';
    std::cout << "Expected:"<<ENGINE_INVALID_SQUARE<<" Got:"<<result << "\033[0m"<<'\n';
  }
  else{
    std::cout<<"\033[32m"<<"✅ Passed! when square="<<square<<'\n';
  }

  square = "10";
  result = to_bitboard(square);
  if (result != ENGINE_INVALID_SQUARE){
    std::cout << "\033[31m" << "❌ Failed at "<< square << '\n';
    std::cout << "Expected:"<<ENGINE_INVALID_SQUARE<<" Got:"<<result << "\033[0m"<<'\n';
  }
  else{
    std::cout<<"\033[32m"<<"✅ Passed! when square="<<square<<'\n';
  }

  square = "h8";
  result = to_bitboard(square);
  if (result != 128){
    std::bitset<64> expected(64);
    std::bitset<64> got(result);

    std::cout << "\033[31m" << "❌ Failed at "<< square << '\n';
    std::cout << "Expected:"<<expected<<" Got:"<<got<< "\033[0m"<<'\n';
  }
  else{
    std::cout<<"\033[32m"<<"✅ Passed! when square="<<square<<'\n';
  }

  square = "e1";
  result = to_bitboard(square);
  if (result != 1152921504606846976){
    std::bitset<64>expected(1152921504606846976); 
    std::bitset<64>got(result);

    std::cout << "\033[31m" << "❌ Failed at "<< square << '\n';
    std::cout << "Expected:"<<expected<<" Got:"<<got<< "\033[0m"<<'\n';
  }
  else{
    std::cout<<"\033[32m"<<"✅ Passed! when square="<<square<<'\n';
  }

};

void test::test_to_standardNOT(){
  piece square;
  std::string result, expected; 

  square = 1152921504606846976;
  result = to_standardNOT(square);
  expected = "e1";
  if (result != expected){
    std::bitset<64> sqr(square);
    std::cout<<"\033[31m"<<"❌ Failed at" << sqr <<'\n';
    std::cout<<"Expected"<<expected<<" Got:"<<result<<'\n';
  }
  else{
    std::cout<<"\033[32m"<<"✅ Passed! when square="<<square<<'\n';
  }

  square = 68719476736;
  result = to_standardNOT(square);
  expected = "e4";
  if (result != expected){
    std::bitset<64> sqr(square);
    std::cout<<"\033[31m"<<"❌ Failed at" << sqr <<'\n';
    std::cout<<"Expected"<<expected<<" Got:"<<result<<'\n';
  }
  else{
    std::cout<<"\033[32m"<<"✅ Passed! when square="<<square<<'\n';
  }

  square = 128;
  result = to_standardNOT(square);
  expected = "h8";
  if (result != expected){
    std::bitset<64> sqr(square);
    std::cout<<"\033[31m"<<"❌ Failed at" << sqr <<'\n';
    std::cout<<"Expected"<<expected<<" Got:"<<result<<'\n';
  }
  else{
    std::cout<<"\033[32m"<<"✅ Passed! when square="<<square<<'\n';
  }

  square = 1;
  result = to_standardNOT(square);
  expected = "a8";
  if (result != expected){
    std::bitset<64> sqr(square);
    std::cout<<"\033[31m"<<"❌ Failed at" << sqr <<'\n';
    std::cout<<"Expected"<<expected<<" Got:"<<result<<'\n';
  }
  else{
    std::cout<<"\033[32m"<<"✅ Passed! when square="<<square<<'\n';
  }


}


int main(){
  test test; 
  test.test_to_bitboard();
  test.test_to_standardNOT();
};

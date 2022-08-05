#include <iostream>

#include <squirrel3/squirrel3.hpp>

int main(int /*argc*/, char** /*argv*/) {
  squirrel3::freeFunction(0);
  bar::freeFunction(1);
  squirrel3bar::freeFunction(2);
  std::cout << std::endl;

  squirrel3::squirrel3::staticFunction(int{0});
  bar::Bar::staticFunction(int{1});
  squirrel3bar::squirrel3Bar::staticFunction(int{2});
  std::cout << std::endl;

  return 0;
}

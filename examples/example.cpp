#include <iostream>

#include <squirrel3/squirrel3.hpp>

int main(int /*argc*/, char** /*argv*/) {
  squirrel3::freeFunction(0);
  std::cout << std::endl;

  squirrel3::Squirrel3::staticFunction(int{0});
  std::cout << std::endl;

  return 0;
}

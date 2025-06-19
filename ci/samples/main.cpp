#include <iostream>

#include <squirrel3/squirrel3.hpp>

int main(int /*argc*/, char** /*argv*/) {
  squirrel3::get1d(42, 2);
  std::cout << std::endl;

  squirrel3::get2d(42, 2);
  std::cout << std::endl;

  return 0;
}

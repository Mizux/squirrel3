#include <iostream>
#include <string>

#include "squirrel3/squirrel3.hpp"

int main(int /*argc*/, char** /*argv*/) {
  auto value = squirrel3::squirrel3(0, 42);
  std::cout << std::to_string(value) << std::endl;

  value = squirrel3::squirrel3(42, 42);
  std::cout << std::to_string(value) << std::endl;

  value = squirrel3::squirrel3(0, 42);
  std::cout << std::to_string(value) << std::endl;

  return 0;
}

#include <squirrel3/squirrel3.hpp>

#include <cstdint>
#include <gtest/gtest.h>

namespace squirrel3 {

TEST(squirrel3, Basic) {
  EXPECT_NO_THROW(squirrel3(42));
}

TEST(squirrel3, Determinism) {
  std::uint32_t res;
  EXPECT_NO_THROW(res = squirrel3(31));
  std::uint32_t res2;
  EXPECT_NO_THROW(res2 = squirrel3(31));
  EXPECT_EQ(res, res2);
}

TEST(squirrel3, uint32) {
  std::uint32_t seed = 42;
  std::uint32_t res;
  EXPECT_NO_THROW(res = squirrel3(31, seed));
  EXPECT_EQ(squirrel3(31, seed), res);
}

} // namespace squirrel3

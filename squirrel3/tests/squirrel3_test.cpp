#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <squirrel3/squirrel3.hpp>

namespace squirrel3 {

TEST_CASE("squirrel3", "[squirrel3]") {
  SECTION("Basic") {
    REQUIRE_NOTHROW(squirrel3(42));
  }
  SECTION("Determinism") {
    std::uint32_t res;
    REQUIRE_NOTHROW(res = squirrel3(31));
    std::uint32_t res2;
    REQUIRE_NOTHROW(res2 = squirrel3(31));
    REQUIRE(res == res2);
  }
}

SCENARIO("squirrel3 Int64", "[squirrel3]") {
  GIVEN("A squirrel3 seed") {
    std::uint32_t seed = 42;
    WHEN("Getting a value") {
      std::uint32_t res;
      REQUIRE_NOTHROW(res = squirrel3(31, seed));
      THEN("The value is same") {
        REQUIRE(squirrel3(31, seed) == res);
      }
    }
  }
}

} // namespace squirrel3
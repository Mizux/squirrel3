#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <numeric>
#include <string>

#include <squirrel3/squirrel3.hpp>

namespace squirrel3 {

TEST_CASE("squirrel3 free function", "[squirrel3]") {
  SECTION("Int Function") { REQUIRE_NOTHROW(freeFunction(42)); }
  SECTION("Int64_t Function") { REQUIRE_NOTHROW(freeFunction(int64_t{42})); }
}

TEST_CASE("String Vector usage", "[squirrel3]") {
  SECTION("Vector of String Output") {
    std::vector<std::string> result;
    REQUIRE_NOTHROW(result = stringVectorOutput(8));
    REQUIRE(result.size() == 8);
    for (const auto& it : result) {
      REQUIRE(it == std::to_string(8));
    }
  }
  SECTION("Vector of String Input by value") {
    std::vector<std::string> data{"1", "2", "3", "4", "5"};
    int                      size = 0;
    REQUIRE_NOTHROW(size = stringVectorInput(data));
    REQUIRE(size == 5);
  }
  SECTION("Vector of String Input by const ref") {
    std::vector<std::string> data{"1", "2", "3", "4", "5"};
    int                      size = 0;
    REQUIRE_NOTHROW(size = stringVectorRefInput(data));
    REQUIRE(size == 5);
  }
}

TEST_CASE("String Jagged Array usage", "[squirrel3]") {
  SECTION("Jagged Array of String Output") {
    std::vector<std::vector<std::string>> result;
    REQUIRE_NOTHROW(result = stringJaggedArrayOutput(8));
    REQUIRE(result.size() == 8);
    for (int i = 0; i < result.size(); ++i) {
      REQUIRE(i + 1 == result[i].size());
    }
    for (int i = 1; i <= result.size(); ++i) {
      const auto& inner = result[i - 1];
      for (const auto& it : inner) {
        REQUIRE(it == std::to_string(i));
      }
    }
  }
  SECTION("Jagged Array of String Input by value") {
    std::vector<std::vector<std::string>> data{{"1", "2", "3"}, {"4", "5"}};
    int                                   size = 0;
    REQUIRE_NOTHROW(size = stringJaggedArrayInput(data));
    REQUIRE(size == 2);
  }
  SECTION("Jagged Array of String Input by const ref") {
    std::vector<std::vector<std::string>> data{{"1", "2", "3"}, {"4", "5"}};
    int                                   size = 0;
    REQUIRE_NOTHROW(size = stringJaggedArrayRefInput(data));
    REQUIRE(size == 2);
  }
}

TEST_CASE("Pair Vector usage", "[squirrel3]") {
  SECTION("Vector of Pair Output") {
    std::vector<std::string> result;
    REQUIRE_NOTHROW(result = stringVectorOutput(8));
    REQUIRE(result.size() == 8);
    for (const auto& it : result) {
      REQUIRE(it == std::to_string(8));
    }
  }
  SECTION("Vector of Pair Input by value") {
    std::vector<std::string> data{"1", "2", "3", "4", "5"};
    int                      size = 0;
    REQUIRE_NOTHROW(size = stringVectorInput(data));
    REQUIRE(size == 5);
  }
  SECTION("Vector of Pair Input by const ref") {
    std::vector<std::string> data{"1", "2", "3", "4", "5"};
    int                      size = 0;
    REQUIRE_NOTHROW(size = stringVectorRefInput(data));
    REQUIRE(size == 5);
  }
}

TEST_CASE("Pair Jagged Array usage", "[squirrel3]") {
  SECTION("Jagged Array of Pair Output") {
    std::vector<std::vector<std::pair<int, int>>> result;
    REQUIRE_NOTHROW(result = pairJaggedArrayOutput(8));
    REQUIRE(result.size() == 8);
    for (int i = 0; i < result.size(); ++i) {
      REQUIRE(i + 1 == result[i].size());
    }
    for (int i = 1; i <= result.size(); ++i) {
      const auto& inner = result[i - 1];
      for (const auto& it : inner) {
        REQUIRE(it == std::make_pair(i, i));
      }
    }
  }
  SECTION("Jagged Array of Pair Input by value") {
    std::vector<std::vector<std::pair<int, int>>> data{{{1, 1}, {2, 2}, {3, 3}}, {{4, 4}, {5, 5}}};
    int                                           size = 0;
    REQUIRE_NOTHROW(size = pairJaggedArrayInput(data));
    REQUIRE(size == 2);
  }
  SECTION("Jagged Array of Pair Input by const ref") {
    std::vector<std::vector<std::pair<int, int>>> data{{{1, 1}, {2, 2}, {3, 3}}, {{4, 4}, {5, 5}}};
    int                                           size = 0;
    REQUIRE_NOTHROW(size = pairJaggedArrayRefInput(data));
    REQUIRE(size == 2);
  }
}

TEST_CASE("squirrel3 static method", "[squirrel3]") {
  SECTION("Int Method") { REQUIRE_NOTHROW(squirrel3::staticFunction(42)); }
  SECTION("Int64_t Method") { REQUIRE_NOTHROW(squirrel3::staticFunction(int64_t{42})); }
}

TEST_CASE("squirrel3::Ctor", "[squirrel3]") {
  SECTION("Default constructor") {
    Squirrel3* b = new Squirrel3();
    REQUIRE(b != nullptr);
  }
}

SCENARIO("squirrel3 Int", "[squirrel3]") {
  GIVEN("A squirrel3 instance") {
    Squirrel3 squirrel3;
    WHEN("Setting a value") {
      REQUIRE_NOTHROW(squirrel3.setInt(42));
      THEN("The value is updated") { REQUIRE(squirrel3.getInt() == 42); }
    }
  }
}

SCENARIO("squirrel3 Int64", "[squirrel3]") {
  GIVEN("A squirrel3 instance") {
    Squirrel3 squirrel3;
    WHEN("Setting a value") {
      REQUIRE_NOTHROW(squirrel3.setInt64(31));
      THEN("The value is updated") { REQUIRE(squirrel3.getInt64() == 31); }
    }
  }
}

TEST_CASE("squirrel3::operator()", "[squirrel3]") {
  SECTION("Debug print") { INFO("squirrel3: " << squirrel3()()); }
}

} // namespace squirrel3

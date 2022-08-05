#pragma once

#include <cstdint>
#include <string>
#include <vector>

//! @namespace squirrel3 The Squirrel3 namespace
namespace squirrel3 {
/*! @brief Returns an unsigned integer containing 32 reasonably-well-scrambled bits.
 * This based on a given (signed) integer input parameter `n` and optional
 * `seed`.  Kind of like looking up a value in an infinitely large
 * non-existent table of previously generated random numbers.
 * @param[in] n position.
 * @param[in] seed optional seed.
 * @return A random 32bits number.*/
inline std::uint32_t squirrel3(std::uint32_t n, std::uint32_t seed=0) {
  // The base bit-noise constants were crafted to have distinctive and interesting
  // bits, and have so far produced excellent experimental test results.
  constexpr std::uint64_t NOISE1 = 0xb5297a4d;  // 0b0110'1000'1110'0011'0001'1101'1010'0100
  constexpr std::uint64_t NOISE2 = 0x68e31da4;  // 0b1011'0101'0010'1001'0111'1010'0100'1101
  constexpr std::uint64_t NOISE3 = 0x1b56c4e9;  // 0b0001'1011'0101'0110'1100'0100'1110'1001
  constexpr std::uint64_t CAP = 1UL << 32;

  std::uint64_t mangled = n;
  mangled *= NOISE1;
  mangled += seed;
  mangled ^= (mangled >> 8);
  mangled += NOISE2;
  mangled ^= (mangled << 8);
  mangled *= NOISE3;
  mangled ^= (mangled >> 8);
  // Cast into uint32_t like the original `Squirrel3`.
  return mangled % CAP;
}

//! @defgroup StringVector Vector of String usage.
//! @{
/*! @brief Test returning a vector of string.
 * @param[in] level Scope level.
 * @return A vector of string.*/
std::vector<std::string> stringVectorOutput(int level);
/*! @brief Test using a vector of string passed by value.
 * @param[in] data Input data.
 * @return The size of the data vector.*/
int stringVectorInput(std::vector<std::string> data);
/*! @brief Test using a vector of string passed by const ref.
 * @param[in] data Input data.
 * @return The size of the data vector.*/
int stringVectorRefInput(const std::vector<std::string>& data);
//! @}

//! @defgroup StringJaggedArray Vector of Vector of String usage.
//! @{
/*! @brief Test returning a jagged array of string.
 * @param level Scope level.
 * @return A jagged array of string.*/
std::vector<std::vector<std::string>> stringJaggedArrayOutput(int level);
/*! @brief Test using a jagged array of string passed by value.
 * @param data Input data.
 * @return The size of the data outer vector.*/
int stringJaggedArrayInput(std::vector<std::vector<std::string>> data);
/*! @brief Test using a jagged array of string passed by const ref.
 * @param data Input data.
 * @return The size of the data outer vector.*/
int stringJaggedArrayRefInput(const std::vector<std::vector<std::string>>& data);
//! @}

//! @defgroup PairVector Vector of Pair usage.
//! @{
/*! @brief Test returning a vector of pair.
 * @param level Scope level.
 * @return A vector of pair.*/
std::vector<std::pair<int, int>> pairVectorOutput(int level);
/*! @brief Test using a vector of pair passed by value.
 * @param data Input data.
 * @return The size of the data vector.*/
int pairVectorInput(std::vector<std::pair<int, int>> data);
/*! @brief Test using a vector of pair passed by const ref.
 * @param data Input data.
 * @return The size of the data vector.*/
int pairVectorRefInput(const std::vector<std::pair<int, int>>& data);
//! @}

//! @defgroup PairJaggedArray Jagged array of Pair<int, int> usage.
//! @{
/*! @brief Test returning a jagged array of pair.
 * @param level Scope level.
 * @return A jagged array of pair.*/
std::vector<std::vector<std::pair<int, int>>> pairJaggedArrayOutput(int level);
/*! @brief Test using a jagged array of pair passed by value.
 * @param data Input data.
 * @return The size of the data outer vector.*/
int pairJaggedArrayInput(std::vector<std::vector<std::pair<int, int>>> data);
/*! @brief Test using a jagged of pair passed by const ref.
 * @param data Input data.
 * @return The size of the data outer vector.*/
int pairJaggedArrayRefInput(const std::vector<std::vector<std::pair<int, int>>>& data);
//! @}

//! @defgroup FreeFunction Free function usage.
//! @{
/*! @brief Free function in squirrel3 namespace.
 * @param level Scope level.*/
void freeFunction(int level);
/*! @brief Free function in squirrel3 namespace.
 * @param level Scope level.*/
void freeFunction(int64_t level);
//! @}

//! @brief Class Squirrel3.
class Squirrel3 {
 public:
  //! @defgroup StaticMembers Static members
  //! @{

  /*! @brief Static method of Squirrel3 class.
   * @param[in] level Scope level.*/
  static void staticFunction(int level);

  /*! @brief Static method of Squirrel3 class.
   * @param[in] level Scope level.*/
  static void staticFunction(int64_t level);

  //! @}

  //! @defgroup IntegerMembers Integer members
  //! @{

  /*! @brief Method (getter) of Squirrel3 class.
   * @return A member value.*/
  int getInt() const;
  /*! @brief Method (setter) of Squirrel3 class.
   * @param[in] input A member value.*/
  void setInt(int input);

  //! @}

  //! @defgroup Int64Members Long Integer members
  //! @{

  /*! @brief Method (getter) of Squirrel3 class.
   * @return A member value.*/
  int64_t getInt64() const;
  /*! @brief Method (setter) of Squirrel3 class.
   * @param[in] input A member value.*/
  void setInt64(int64_t input);

  //! @}

  //! @brief Print object for debug.
  std::string operator()() const;

 private:
  int     _intValue   = 0;
  int64_t _int64Value = 0;
};
} // namespace squirrel3

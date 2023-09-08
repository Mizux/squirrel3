#pragma once

#include <cstdint>

//! @namespace squirrel3 The Squirrel3 namespace
namespace squirrel3 {
/*! @brief Returns an unsigned integer containing 32 reasonably-well-scrambled bits.
 * This based on a given (signed) integer input parameter `n` and optional
 * `seed`.  Kind of like looking up a value in an infinitely large
 * non-existent table of previously generated random numbers.
 * @param[in] n position.
 * @param[in] seed seed.
 * @return A random unsigned 32bits number.*/
inline std::uint32_t squirrel3(std::uint32_t n, std::uint32_t seed) {
  // The base bit-noise constants were crafted to have distinctive and interesting
  // bits, and have so far produced excellent experimental test results.
  constexpr std::uint64_t NOISE1 = 0xb5297a4d; // 0b0110'1000'1110'0011'0001'1101'1010'0100
  constexpr std::uint64_t NOISE2 = 0x68e31da4; // 0b1011'0101'0010'1001'0111'1010'0100'1101
  constexpr std::uint64_t NOISE3 = 0x1b56c4e9; // 0b0001'1011'0101'0110'1100'0100'1110'1001
  constexpr std::uint64_t CAP    = 1UL << 32;

  std::uint64_t mangled = n;
  mangled *= NOISE1;
  mangled += seed;
  mangled ^= (mangled >> 8);
  mangled += NOISE2;
  mangled ^= (mangled << 8);
  mangled *= NOISE3;
  mangled ^= (mangled >> 8);
  // Cast into uint32_t like the original `Squirrel3`.
  return mangled & (CAP - 1);
}

constexpr std::uint64_t PRIME1 = 198491317;
constexpr std::uint64_t PRIME2 = 6542989;

inline std::uint32_t get1d(std::uint32_t x = 0, std::uint32_t seed = 0) {
  return squirrel3(x, seed);
}

inline std::uint32_t get2d(std::uint32_t x = 0, std::uint32_t y = 0, std::uint32_t seed = 0) {
  return get1d(x + (PRIME1 * y), seed);
}

inline std::uint32_t
get3d(std::uint32_t x = 0, std::uint32_t y = 0, std::uint32_t z = 0, std::uint32_t seed = 0) {
  return get1d(x + (PRIME1 * y) + (PRIME2 * z), seed);
}

//! @defgroup NormalizedFloat normalized float version.
//! @ref get1df(), @ref get2df() and @ref get3df() each return a float between 0 and 1.
//! @{

inline float get1df(std::uint32_t x = 0, std::uint32_t seed = 0) {
  return get1d(x, seed) / float{0xFFFFFFFF};
}

inline float get2df(std::uint32_t x = 0, std::uint32_t y = 0, std::uint32_t seed = 0) {
  return get2d(x, y, seed) / float{0xFFFFFFFF};
}

inline float get3df(std::uint32_t x = 0, std::uint32_t y = 0, std::uint32_t z = 0, std::uint32_t seed = 0) {
  return get3d(x, y, z, seed) / float{0xFFFFFFFF};
}

//! @}

} // namespace squirrel3

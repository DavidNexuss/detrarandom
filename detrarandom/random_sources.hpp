#pragma once
#include <cstdint>
#include <limits>
#include <random>

#define RANDOM_FUNCTIONS                           \
                                                   \
  inline float                                     \
  randf() {                                        \
                                                   \
    return randi() /                               \
      float(std::numeric_limits<uint32_t>::max()); \
  }                                                \
                                                   \
                                                   \
  inline bool                                      \
  randb() { return randi() % 2; }


namespace random_sources {

struct Standard {
  std::random_device                      rd;
  std::uniform_int_distribution<uint32_t> dist;

  Standard() :
    dist(uint32_t(0), std::numeric_limits<uint32_t>::max()) {}

  uint32_t randi() {
    return dist(rd);
  }

  RANDOM_FUNCTIONS
};

struct CStandard {
  CStandard() {
    srand(0);
  }

  uint32_t randi() {
    return rand();
  }

  RANDOM_FUNCTIONS
};

struct XORand {
  uint32_t state;

  XORand(uint32_t seed = 2463534242u) :
    state(seed) {}

  inline uint32_t randi() {
    uint32_t x = state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    state = x;
    return x;
  }
  RANDOM_FUNCTIONS
};

struct XORand128 {
  uint64_t s[2];

  XORand128(uint64_t seed1 = 0x123456789abcdefULL, uint64_t seed2 = 0xfedcba987654321ULL) {
    s[0] = seed1;
    s[1] = seed2;
  }

  inline uint64_t randi() {
    uint64_t x = s[0];
    uint64_t y = s[1];
    s[0]       = y;
    x ^= x << 23;
    s[1] = x ^ y ^ (x >> 17) ^ (y >> 26);
    return s[1] + y;
  }

  RANDOM_FUNCTIONS
};

#undef RANDOM_FUNCTIONS

} // namespace random_sources

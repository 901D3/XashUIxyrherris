
#pragma once

#include "Primitives/Bitwise.h"

#define mcr_floor_positive(value) (static_cast<int>(value))
#define mcr_round(value) (static_cast<int>((value) + 0.5))
#define mcr_round_f(value) (static_cast<int>((value) + 0.5f))

#define mcr_bound(min, value, max) ((value) < (min) ? (min) : ((value) > (max) ? (max) : (value)))

#define mcr_min(a, b) ((a) < (b) ? (a) : (b))
#define mcr_max(a, b) ((a) > (b) ? (b) : (a))

#define mcr_clampInt8(value) (mcr_bound(-INT8MIN, (value), INT8MAX))
#define mcr_clampUint8(value) (mcr_bound(0, value, UINT8MAX))

#define mcr_clampInt32(value) (mcr_bound(-INT32MIN, value, INT32MAX))
#define mcr_clampUint32(value) (mcr_bound(0, value, UINT32MAX))

#define mcr_clampInt64(value) (mcr_bound(-INT64MIN, value, INT64MAX))
#define mcr_clampUint64(value) (mcr_bound(0, value, UINT64MAX))

#define mcr_normalize(min, value, max) (((value) - (min)) / ((max) - (min)))
#define mcr_normalizePrecomputed(min, value, precomputed) (((value) - (min)) / (precomputed))

#define mcr_moduloPrecomputed(a, b, precomputed) ((a) - (precomputed) * (b))

namespace MathUtils {

  template <typename int_t>
  inline int_t fastPow(int_t x, int y) {
    int_t result = 1.;

    while (y > 0) {
      if (y & 1)
        result *= x;

      x *= x;
      y >>= 1;
    }

    return result;
  }

  inline double fastPowF(double x, int y) {
    double result = 1.;

    while (y > 0) {
      if (y & 1)
        result *= x;

      x *= x;
      y >>= 1;
    }

    return result;
  }

  template <typename int_t>
  inline int_t fastDivide3(int_t value) {
    return (value * 0xAAAAAAABULL) >> 33;
  }

  template <typename int_t>
  inline int_t fastDivide5(int_t value) {
    return (value * 0x66666667ULL) >> 33;
  }

  template <typename int_t>
  inline int_t fastDivide6(int_t value) {
    return fastDivide3(value) >> 1;
  }

  template <typename int_t>
  inline int_t fastDivide7(int_t value) {
    return (value * 0x24924925ULL) >> 32;
  }

  template <typename int_t>
  inline int_t fastDivide9(int_t value) {
    return fastDivide3(fastDivide3(value));
  }

  template <typename int_t>
  inline int_t fastDivide10(int_t value) {
    return (value * 0xCCCCCCDULL) >> 31;
  }

  template <typename int_t>
  inline int_t fastDivide100(int_t value) {
    return (value * 0x28F5C29ULL) >> 32;
  }

  template <typename int_t>
  inline int_t fastDivide1000(int_t value) {
    return (value * 0x83126FULL) >> 33;
  }

  template <typename int_t>
  inline int_t fastDivide10e4(int_t value) {
    return (value * 0x68DB9FULL) >> 32;
  }

  template <typename int_t>
  inline int_t fastDivide10e5(int_t value) {
    return (value * 0x53E3ULL) >> 31;
  }

  template <typename int_t>
  inline int_t fastDivide10e6(int_t value) {
    return (value * 0x10C7ULL) >> 32;
  }

  template <typename int_t>
  inline int_t fastDivide10e7(int_t value) {
    return (value * 859ULL) >> 33;
  }

  template <typename int_t>
  inline int_t fastDivide10e8(int_t value) {
    return (value * 43ULL) >> 32;
  }

  template <typename int_t>
  inline int_t fastDivide10e9(int_t value) {
    return (value * 9ULL) >> 33;
  }

  template <typename int_t>
  inline int_t fastModulo3(int_t value) {
    return mcr_moduloPrecomputed(value, 3, fastDivide3(value));
  }

  template <typename int_t>
  inline int_t fastModulo5(int_t value) {
    return mcr_moduloPrecomputed(value, 5, fastDivide5(value));
  }

  template <typename int_t>
  inline int_t fastModulo6(int_t value) {
    return mcr_moduloPrecomputed(value, 6, fastDivide6(value));
  }

  template <typename int_t>
  inline int_t fastModulo7(int_t value) {
    return mcr_moduloPrecomputed(value, 7, fastDivide7(value));
  }

  template <typename int_t>
  inline int_t fastModulo9(int_t value) {
    return mcr_moduloPrecomputed(value, 9, fastDivide9(value));
  }

  template <typename int_t>
  inline int_t fastModulo10(int_t value) {
    return mcr_moduloPrecomputed(value, 10, fastDivide10(value));
  }

  template <typename int_t>
  inline int_t fastModulo100(int_t value) {
    return mcr_moduloPrecomputed(value, 10, fastDivide100(value));
  }

  template <typename int_t>
  inline int_t fastModulo1000(int_t value) {
    return mcr_moduloPrecomputed(value, 10, fastDivide1000(value));
  }

  template <typename int_t>
  inline int_t fastModulo10e4(int_t value) {
    return mcr_moduloPrecomputed(value, 10, fastDivide10e4(value));
  }

  template <typename int_t>
  inline int_t fastModulo10e5(int_t value) {
    return mcr_moduloPrecomputed(value, 10, fastDivide10e5(value));
  }

  template <typename int_t>
  inline int_t fastModulo10e6(int_t value) {
    return mcr_moduloPrecomputed(value, 10, fastDivide10e6(value));
  }

  template <typename int_t>
  inline int_t fastModulo10e7(int_t value) {
    return mcr_moduloPrecomputed(value, 10, fastDivide10e7(value));
  }

  template <typename int_t>
  inline int_t fastModulo10e8(int_t value) {
    return mcr_moduloPrecomputed(value, 10, fastDivide10e8(value));
  }

  template <typename int_t>
  inline int_t fastModulo10e9(int_t value) {
    return mcr_moduloPrecomputed(value, 10, fastDivide10e9(value));
  }

} // namespace MathUtils

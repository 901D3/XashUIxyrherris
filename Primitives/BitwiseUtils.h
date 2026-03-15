
#pragma once

#define mcr_bitUint(n) (1U << (n))
#define mcr_bitUlonglong(n) (1ULL << (n))

namespace BitwiseUtils {

  inline unsigned int firstBitIndex(unsigned int mask) {
    unsigned int i = 0;

    for (; !(mcr_bitUint(i) & mask); i++)
      ;

    return i;
  }

  inline unsigned int countBits(unsigned int mask) {
    unsigned int i = 0;

    for (; mask; mask >>= 1)
      i += mask & 1;

    return i;
  }

} // namespace BitwiseUtils

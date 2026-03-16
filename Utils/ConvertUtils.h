
#pragma once

#include "ProjectUtils/Utils.h"
#include "Utils/MathUtils.h"

namespace ConvertUtils {

  template <typename int_t>
  inline int_t fastAToInt(const char *string) {
    int_t value = 0;
    int sign = 1;

    if (*string == '-') {
      sign = -1;
      string++;
    }

    unsigned char c;
    while ((c = *string - '0') < 10) {
      value = value * 10 + c;
      ++string;
    }

    return value * sign;
  }

  template <typename int_t>
  inline int_t fastAToUint(const char *string) {
    int_t value = 0;

    unsigned char c;
    while ((c = *string - '0') < 10) {
      value = value * 10 + c;
      ++string;
    }

    return value;
  }

  template <typename enum_t>
  inline enum_t fastAToEnum(const char *string) {
    return static_cast<enum_t>(fastAToInt<long long>(string));
  }

  template <typename fp_t>
  inline fp_t fastAToFloat(const char *string) {
    fp_t value = 0;
    int sign = 1;

    if (*string == '-') {
      string++;

      sign = -1;
    }

    while (*string >= '0' && *string <= '9')
      value = value * 10 + (*string++ - '0');

    if (*string == '.') {
      ++string;

      fp_t frac = 1;

      while (*string >= '0' && *string <= '9') {
        frac *= 0.1;
        value += (*string++ - '0') * frac;
      }
    }

    return value * sign;
  }

  template <typename int_t>
  inline void fastIntToString(char *output, int_t value) {
    char *ptr = output;

    bool isNegative = value < 0;
    if (isNegative)
      value = -value;

    if (value == 0) {
      *ptr++ = '0';
      *ptr = 0;
      return;
    }

    while (value) {
      *ptr++ = '0' + (value % 10);
      value /= 10;
    }

    if (isNegative)
      *ptr++ = '-';

    *ptr = '\0';

    char *start = output;
    char *end = ptr - 1;

    while (start < end) {
      char temp = *start;
      *start++ = *end;
      *end-- = temp;
    }
  }

  template <typename int_t>
  inline void fastUintToString(char *output, int_t value) {
    char *ptr = output;

    if (value == 0) {
      *ptr++ = '0';
      return;
    }

    while (value) {
      *ptr++ = '0' + (value % 10);
      value = MathUtils::fastDivide10(value);
    }

    *ptr = '\0';

    char *start = output;
    char *end = ptr - 1;

    while (start < end) {
      char temp = *start;
      *start++ = *end;
      *end-- = temp;
    }
  }

  // fast but fragile float to string
  template <int WHOLE, int FRAC>
  inline void fastFloatToString(char *output, float value) {
    int x = mcr_round(value * FRAC);

    int whole = x / FRAC;
    int frac = mcr_moduloPrecomputed(x, FRAC, whole);

    char *ptr = output;

    if (WHOLE >= 1000000000 && whole >= 1000000000) {
      *ptr++ = '0' + MathUtils::fastDivide10e9(whole);
      whole = MathUtils::fastModulo10e9(whole);
    }
    if (WHOLE >= 100000000 && whole >= 100000000) {
      *ptr++ = '0' + MathUtils::fastDivide10e8(whole);
      whole = MathUtils::fastModulo10e8(whole);
    }
    if (WHOLE >= 10000000 && whole >= 10000000) {
      *ptr++ = '0' + MathUtils::fastDivide10e7(whole);
      whole = MathUtils::fastModulo10e7(whole);
    }
    if (WHOLE >= 1000000 && whole >= 1000000) {
      *ptr++ = '0' + MathUtils::fastDivide10e6(whole);
      whole = MathUtils::fastModulo10e6(whole);
    }
    if (WHOLE >= 100000 && whole >= 100000) {
      *ptr++ = '0' + MathUtils::fastDivide10e5(whole);
      whole = MathUtils::fastModulo10e5(whole);
    }
    if (WHOLE >= 10000 && whole >= 10000) {
      *ptr++ = '0' + MathUtils::fastDivide10e4(whole);
      whole = MathUtils::fastModulo10e4(whole);
    }
    if (WHOLE >= 1000 && whole >= 1000) {
      *ptr++ = '0' + MathUtils::fastDivide1000(whole);
      whole = MathUtils::fastModulo1000(whole);
    }
    if (WHOLE >= 100 && whole >= 100) {
      *ptr++ = '0' + MathUtils::fastDivide100(whole);
      whole = MathUtils::fastModulo100(whole);
    }
    if (whole >= 10) {
      *ptr++ = '0' + MathUtils::fastDivide10(whole);
      whole = MathUtils::fastModulo10(whole);
    }

    *ptr++ = '0' + whole;

    if (FRAC > 0) {
      *ptr++ = '.';
      int div = MathUtils::fastDivide10(FRAC);

      while (div > 0) {
        *ptr++ = '0' + frac / div;
        frac %= div;
        div = MathUtils::fastDivide10(div);
      }
    }

    *ptr = 0;
  }

} // namespace ConvertUtils

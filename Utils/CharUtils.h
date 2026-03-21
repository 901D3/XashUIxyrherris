
#pragma once

#include <string>
#include <ctype.h>

namespace CharUtils {

  inline unsigned int UTF8ToUnicodeCP(const std::string &string, int &index) {
    unsigned char character = string[index];

    if (character < 0x80)
      return string[index++];
    else if ((character >> 5) == 0x6) {
      unsigned int codepoint = ((character & 0x1F) << 6) | (string[index + 1] & 0x3F);
      index += 2;
      return codepoint;
    } else if ((character >> 4) == 0xE) {
      unsigned int codepoint = ((character & 0x0F) << 12) | ((string[index + 1] & 0x3F) << 6) | (string[index + 2] & 0x3F);
      index += 3;
      return codepoint;
    }

    index++;
    return '?';
  }

  inline void unicodeCPToCP1251(unsigned int &codepoint) {
    // А–Я
    if (codepoint >= 0x0410 && codepoint <= 0x042F)
      codepoint -= 0x410 - 0xC0;

    // а–я
    else if (codepoint >= 0x0430 && codepoint <= 0x044F)
      codepoint -= 0x430 - 0xE0;

    // Ё
    else if (codepoint == 0x0401)
      codepoint = 0xA8;

    // ё
    else if (codepoint == 0x0451)
      codepoint = 0xB8;
  }

  inline int caseInsensitiveCompare(const char *string1, const char *string2) {
    while (*string1 && *string2) {
      char c1 = tolower(static_cast<unsigned char>(*string1));
      char c2 = tolower(static_cast<unsigned char>(*string2));
      if (c1 != c2)
        return static_cast<unsigned char>(c1) - static_cast<unsigned char>(c2);

      string1++;
      string2++;
    }

    return 0;
  }

} // namespace CharUtils

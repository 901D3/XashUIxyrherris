
#pragma once

#include <string>

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

} // namespace CharUtils

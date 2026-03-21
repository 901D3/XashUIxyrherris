
#pragma once

#include "Primitives/Color.h"

namespace ColorUtils {

  inline unsigned int packRGBA(
    unsigned char r,
    unsigned char g,
    unsigned char b,
    unsigned char a) {

    return (
      (static_cast<unsigned int>(r) << 24)
      | (static_cast<unsigned int>(g) << 16)
      | (static_cast<unsigned int>(b) << 8)
      | static_cast<unsigned int>(a));
  }

  inline unsigned int packRGB(
    unsigned char r,
    unsigned char g,
    unsigned char b) {

    return (
      (static_cast<unsigned int>(r) << 16)
      | (static_cast<unsigned int>(g) << 8)
      | static_cast<unsigned int>(b));
  }

  inline unsigned int packRGBAFromStruct(RGBAColor *color) {
    return packRGBA(color->r, color->g, color->b, color->a);
  }

  inline unsigned int packRGBFromStruct(RGBColor *color) {
    return packRGB(color->r, color->g, color->b);
  }

  inline void unpackRGBA(
    unsigned int rgba,
    unsigned char *r,
    unsigned char *g,
    unsigned char *b,
    unsigned char *a) {

    *r = (rgba >> 24) & 0xFF;
    *g = (rgba >> 16) & 0xFF;
    *b = (rgba >> 8) & 0xFF;
    *a = rgba & 0xFF;
  }

  inline void unpackRGB(
    unsigned int rgb,
    unsigned char *r,
    unsigned char *g,
    unsigned char *b) {

    *r = (rgb >> 16) & 0xFF;
    *g = (rgb >> 8) & 0xFF;
    *b = rgb & 0xFF;
  }

  inline unsigned short RGBX8888ToRGB565(
    unsigned char r,
    unsigned char g,
    unsigned char b) {

    return ((r << 8) | (g << 3) | (b >> 3));
  }

  inline unsigned short packedRGBX8888ToRGB565(unsigned int color) {
    unsigned char r = (color >> 24) & 0xFF;
    unsigned char g = (color >> 16) & 0xFF;
    unsigned char b = (color >> 8) & 0xFF;

    return RGBX8888ToRGB565(r, g, b);
  }

} // namespace ColorUtils


#pragma once

#include "EngineStuff.h"

inline void fillPackedRGBA(int x, int y, int width, int height, unsigned int color) {
  engineFunctions->pfnFillRGBA(
    x, y, width, height,
    color & 0xFF,
    (color >> 8) & 0xFF,
    (color >> 16) & 0xFF,
    (color >> 24) & 0xFF);
}

typedef struct {
  unsigned char r, g, b, a;
} RGBAColor;

inline unsigned int packRGBA(
  unsigned char r,
  unsigned char g,
  unsigned char b,
  unsigned char a) {

  return (
    static_cast<unsigned int>(r) | (static_cast<unsigned int>(g) << 8) | (static_cast<unsigned int>(b) << 16) | (static_cast<unsigned int>(a) << 24));
}

inline unsigned int packRGBAFromStruct(RGBAColor *color) {
  return (
    static_cast<unsigned int>(color->r) | (static_cast<unsigned int>(color->g) << 8) | (static_cast<unsigned int>(color->b) << 16) | (static_cast<unsigned int>(color->a) << 24));
}

inline RGBAColor unpackRGBA(
  unsigned int rgba,
  unsigned char *r,
  unsigned char *g,
  unsigned char *b,
  unsigned char *a) {

  *r = rgba;
  *g = rgba >> 8;
  *b = rgba >> 16;
  *a = rgba >> 24;
}

inline RGBAColor unpackRGBAToStruct(unsigned int rgba) {
  return {
    static_cast<unsigned char>(rgba),
    static_cast<unsigned char>(rgba >> 8),
    static_cast<unsigned char>(rgba >> 16),
    static_cast<unsigned char>(rgba >> 24)};
}

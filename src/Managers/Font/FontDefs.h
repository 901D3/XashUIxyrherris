
#pragma once

#include "engine/menu_int.h"

typedef enum {
  FONT_BUILTIN = 0,
  FONT_COUNT,
} FontEnums;

typedef struct {
  int
    atlasX, // position of the glyph on the atlas
    atlasY,

    width,
    height;
} BitmapGlyph;

typedef struct {
  FontEnums font;
  HIMAGE fontHImage;

  int atlasWidth, atlasHeight;

  BitmapGlyph* glyphs; // ptr to array
  unsigned int glyphCount;

  int lineHeight, base;

} BitmapFontContext;

typedef struct {
  int
    atlasX, // position of the glyph on the atlas
    atlasY,

    width, // B
    height,

    leftBearing, // A
    // rightBearing, // rightBearing = advance - (leftBearing + width); // C

    advanceX,

    bearingY;
} Glyph;

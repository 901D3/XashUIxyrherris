
#include "EngineStuff.h" // engineFunctions
#include "Managers/Font/Font.h"
#include "Data/ArialFont.h"

BitmapFontContext bitmapFontContext;

// use builtin menu font for now
void bitmapFontInitBuiltInFont(void) {
  bitmapFontContext.lineHeight = ARIAL_FONT_GLYPH_HEIGHT;
  bitmapFontContext.base = ARIAL_FONT_GLYPH_HEIGHT;

  const int glyphCount = ARIAL_FONT_GLYPH_COUNT_X * ARIAL_FONT_GLYPH_COUNT_Y;

  bitmapFontContext.glyphCount = glyphCount;

  BitmapGlyph *glyphs = new BitmapGlyph[glyphCount]; // future proof for custom fonts

  // filling glyphs[]
  for (int y = 0; y < ARIAL_FONT_GLYPH_COUNT_Y; y++) {
    int yOffs = y * ARIAL_FONT_GLYPH_COUNT_X;
    int atlasY = ARIAL_FONT_GLYPH_HEIGHT * y;

    for (int x = 0; x < ARIAL_FONT_GLYPH_COUNT_X; x++) {
      int idx = yOffs + x;

      glyphs[idx].atlasX = ARIAL_FONT_GLYPH_WIDTH * x;
      glyphs[idx].atlasY = atlasY;

      glyphs[idx].width = ARIAL_FONT_GLYPH_WIDTH;
      glyphs[idx].height = ARIAL_FONT_GLYPH_HEIGHT;
    }
  }

  bitmapFontContext.glyphs = glyphs;

  // load the atlas image, save the HIMAGE value that the function returns, it acts like an image id
  bitmapFontContext.fontHImage = engineFunctions->pfnPIC_Load(
    "#XASH_SYSTEMFONT_001.bmp",
    ARIAL_FONT_ATLAS,
    ARIAL_FONT_ATLAS_LENGTH,
    0);

  bitmapFontContext.atlasWidth = engineFunctions->pfnPIC_Width(bitmapFontContext.fontHImage);
  bitmapFontContext.atlasHeight = engineFunctions->pfnPIC_Height(bitmapFontContext.fontHImage);
}

void bitmapFontFree(void) {
  if (bitmapFontContext.glyphs) {
    delete[] bitmapFontContext.glyphs;
    bitmapFontContext.glyphs = nullptr;
  }

  bitmapFontContext.glyphCount = bitmapFontContext.lineHeight = bitmapFontContext.base = bitmapFontContext.fontHImage = 0;
}

// TODO: add feature for loading custom bitmap font without having to restart game
void bitmapFontLoadCustomFont(void) {
}

void bitmapFontInit(FontEnums font) {
  bitmapFontFree(); // free the old/previous font(if any)

  if (font == FONT_BUILTIN)
    bitmapFontInitBuiltInFont();

  bitmapFontContext.font = font;
}

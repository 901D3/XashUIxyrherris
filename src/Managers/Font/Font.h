
#pragma once

#include "Managers/Font/FontDefs.h"

extern BitmapFontContext bitmapFontContext;

extern void bitmapFontInit(FontEnums font); // initialize font
extern void bitmapFontFree(void);           // free the glyph stack

// TODO: add feature for loading custom font without having to restart game
extern void bitmapFontLoadCustomFont(void);

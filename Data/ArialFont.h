
#pragma once

#include <stdint.h> // uint8_t
typedef uint8_t byte;

#define ARIAL_FONT_GLYPH_COUNT_X 16
#define ARIAL_FONT_GLYPH_COUNT_Y 16
#define ARIAL_FONT_ATLAS_WIDTH 256
#define ARIAL_FONT_ATLAS_HEIGHT 256
#define ARIAL_FONT_MAX_VALUE 16
#define ARIAL_FONT_GLYPH_WIDTH 16
#define ARIAL_FONT_GLYPH_HEIGHT 16

extern const byte ARIAL_FONT_ATLAS[];
extern const unsigned int ARIAL_FONT_ATLAS_LENGTH;

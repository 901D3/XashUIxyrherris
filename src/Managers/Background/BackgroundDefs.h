
#pragma once

#include "menu_int.h"

#define MAX_BITMAP_BACKGROUND 64
#define BACKGROUND_SPLASH_WON "gfx/shell/splash.bmp"

typedef enum {
  BACKGROUND_SRC_STEAM = 0,
  BACKGROUND_SRC_WON,
  BACKGROUND_SRC_COUNT
} BackgroundSrcEnums;

typedef enum {
  BACKGROUND_CUSTOM = 0,
  BACKGROUND_CENTER,
  BACKGROUND_FIT,
  BACKGROUND_FILL,
  BACKGROUND_STRETCH,
  BACKGROUND_STRETCH_HORIZONTALLY,
  BACKGROUND_STRETCH_VERTICALLY,
  BACKGROUND_TRANSFORM_STYLE_COUNT
} BackgroundTransformStyleEnums;

typedef struct {
  BackgroundSrcEnums backgroundSrc;

  // use same index for all 3 arrays
  HIMAGE backgroundHImage[MAX_BITMAP_BACKGROUND];
  int backgroundX[MAX_BITMAP_BACKGROUND];
  int backgroundY[MAX_BITMAP_BACKGROUND];
  int backgroundWidth[MAX_BITMAP_BACKGROUND];
  int backgroundHeight[MAX_BITMAP_BACKGROUND];
  int backgroundCount;
  int background;

  int width;
  int height;

} BitmapBackgroundContext;


#pragma once

#include "common/xash3d_types.h"
#include "Base.h"

#include "Primitives/Bitwise.h"

#define WINDOW_WIDTH (globalVars->scrWidth)
#define WINDOW_HEIGHT (globalVars->scrHeight)

#define UI_BASE_WIDTH 1024
#define UI_BASE_HEIGHT 768

#define UI_TARGET_ASPECT_WIDTH 4
#define UI_TARGET_ASPECT_HEIGHT 3

typedef enum {
  ALIGMENT_LEFT = 1,
  ALIGMENT_TOP = mcr_bitUint(1),
  ALIGMENT_RIGHT = mcr_bitUint(2),
  ALIGMENT_BOTTOM = mcr_bitUint(3),

  ALIGMENT_TOP_LEFT = BORDER_TOP | BORDER_LEFT,
  ALIGMENT_TOP_RIGHT = BORDER_TOP | BORDER_RIGHT,
  ALIGMENT_BOTTOM_LEFT = BORDER_BOTTOM | BORDER_LEFT,
  ALIGMENT_BOTTOM_RIGHT = BORDER_BOTTOM | BORDER_RIGHT
} Aligment;

typedef struct {
  int x, y;
} Position;

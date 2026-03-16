
#pragma once

#include "common/xash3d_types.h"
#include "Base.h"

#include "Primitives/Bitwise.h"

#include "Utils/BitwiseUtils.h"

#define WINDOW_WIDTH (globalVars->scrWidth)
#define WINDOW_HEIGHT (globalVars->scrHeight)

#define UI_BASE_WIDTH 1024
#define UI_BASE_HEIGHT 768

#define UI_TARGET_ASPECT_WIDTH 4
#define UI_TARGET_ASPECT_HEIGHT 3

typedef enum {
  ALIGNMENT_LEFT = 1,
  ALIGNMENT_TOP = mcr_bitUint(1),
  ALIGNMENT_RIGHT = mcr_bitUint(2),
  ALIGNMENT_BOTTOM = mcr_bitUint(3),

  ALIGNMENT_TOP_LEFT = ALIGNMENT_TOP | ALIGNMENT_LEFT,
  ALIGNMENT_TOP_RIGHT = ALIGNMENT_TOP | ALIGNMENT_RIGHT,
  ALIGNMENT_BOTTOM_LEFT = ALIGNMENT_BOTTOM | ALIGNMENT_LEFT,
  ALIGNMENT_BOTTOM_RIGHT = ALIGNMENT_BOTTOM | ALIGNMENT_RIGHT
} Alignment;

typedef struct {
  int x, y;
} Position;


#pragma once

#include "Primitives/Transform.h"

#define UI_BUTTONS_WIDTH 250
#define UI_BUTTONS_HEIGHT UI_ITEMMARGINY

#define UI_BANNER_POSX 0
#define UI_BANNER_POSY 0
#define UI_BANNER_WIDTH 768
#define UI_BANNER_HEIGHT 128

#define UI_ITEMMARGINX 10
#define UI_ITEMMARGINY 22

#define UI_BOTTOM_BUTTON_POSX (SCREEN_WIDTH - 60)
#define UI_BOTTOM_BUTTON_POSY (SCREEN_HEIGHT - 50)

extern void buttonAlignmentGenerateList(
  Position *positions,
  int offsetX,
  int offsetY,
  int spaceX,
  int spaceY,
  const int count);

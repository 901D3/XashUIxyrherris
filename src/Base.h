/**
 * Base.h - miscellaneous?
 */

#pragma once

#include "XashEngineRelated/XashKey.h"

#include "EngineStuff.h"
#include "UIDefs.h"
#include "Menus/MenuDefs.h"

#define UI_BASE_WIDTH 1024
#define UI_BASE_HEIGHT 768

#define UI_TARGET_ASPECT_WIDTH 4
#define UI_TARGET_ASPECT_HEIGHT 3

extern UIContext globalUIContext;
extern UIMouseContext globalUIMouseContext;
extern UIKeyContext globalUIKeyContext;

extern void fillPackedRGBA(int x, int y, int width, int height, unsigned int rgba);

extern void mouseEventsLog();
extern void mouseEventsReset();

extern void switchMenu(MenuEnums menu);
extern void navigateToMenu(MenuEnums menu);
extern void goBackToLastMenu();

extern void updateUIDisplayDimensionAndShifts();
extern void updateElementsScaleAndShifts();

extern void setKeyDestWrapper(KeyDestEnums keyDest);

GAME_EXPORT extern void _mouseMove(int x, int y);
extern void updateUI();
GAME_EXPORT extern int _baseVideoInit();
GAME_EXPORT extern void _baseInit();

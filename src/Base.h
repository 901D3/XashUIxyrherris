/**
 * Base.h - miscellaneous?
 */

#pragma once

#include "EngineStuff.h"

#include "Menus/MenuDefs.h"

#include "UIDefs.h"

#include "Primitives/Key.h"

extern UIContext globalUIContext;
extern UIMouseContext globalUIMouseContext;
extern UIKeyContext globalUIKeyContext;

extern void mouseEventsLog();
extern void mouseEventsReset();

extern void switchMenu(MenuEnums menu);
extern void navigateToMenu(MenuEnums menu);
extern void goBackToLastMenu();

extern void updateUIDisplayDimensionAndShifts();
extern void updateElementsScaleAndShifts();

extern void setKeyDestWrapper(KeyDestEnums keyDest);

extern void mouseMove(int x, int y);
extern void updateUI();
GAME_EXPORT extern int _baseVideoInit();
GAME_EXPORT extern void _baseInit();

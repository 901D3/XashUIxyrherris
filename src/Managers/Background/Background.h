/**
 * Background.h - background manager
 */

#pragma once

#include "Managers/Background/BackgroundDefs.h"

extern BitmapBackgroundContext bitmapBackgroundContext;

extern bool bitmapBackgroundInitSteamBackground(bool HDBackground, bool gameDirOnly);
extern bool bitmapBackgroundInitWONBackground(bool gameDirOnly);
extern bool bitmapBackgroundPushBack(HIMAGE hImage, int x, int y, unsigned int width, unsigned int height);
extern void bitmapBackgroundTransformStyleSwitch(void);
extern void bitmapBackgroundRender(void);
extern void bitmapBackgroundFree(void);
extern void bitmapBackgroundInit(BackgroundSrcEnums background);

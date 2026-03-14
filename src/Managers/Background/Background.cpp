
#include "extdll_menu.h"
#include "EngineStuff.h"
#include "Cvars/Cvars.h"

#include "Managers/Background/Background.h"

#include "Primitives/Transform.h"

#include "Utils/ConvertUtils.h"
#include "Utils/MathUtils.h"
#include "Utils/Utils.h"

BitmapBackgroundContext bitmapBackgroundContext;

bool bitmapBackgroundInitSteamBackground(bool HDBackground, bool gameDirOnly) {
  char token[4096];
  char *backgroundLayoutFile;

  // debug stuff
  if (FBitSet(globalGameInfo->flags, GFL_HD_BACKGROUND)) {
    mcr_ConsoleDebugLog("gameinfo uses HD background");
    mcr_ConsoleDebugLog("Loading resource/HD_BackgroundLayout.txt...");
    backgroundLayoutFile = (char *)engineFunctions->COM_LoadFile("resource/HD_BackgroundLayout.txt", 0);
  } else if (HDBackground) {
    mcr_ConsoleDebugLog("explicitly use HD background");
    mcr_ConsoleDebugLog("loading resource/HD_BackgroundLayout.txt...");
    backgroundLayoutFile = (char *)engineFunctions->COM_LoadFile("resource/HD_BackgroundLayout.txt", 0);
  }

  if (!backgroundLayoutFile) {
    mcr_ConsoleDebugLog("Failed to load resource/HD_BackgroundLayout.txt");
    mcr_ConsoleDebugLog("Fallback to resource/BackgroundLayout.txt...");
    backgroundLayoutFile = (char *)engineFunctions->COM_LoadFile("resource/BackgroundLayout.txt", 0);
  }

  if (!backgroundLayoutFile) {
    mcr_ConsoleDebugLog("Failed to load resource/BackgroundLayout.txt...");
    return false;
  }

  char *parsedData = backgroundLayoutFile;

  parsedData = extendedFunctions->pfnParseFile(parsedData, token, sizeof(token), 0, nullptr);
  if (!parsedData || strcmp(token, "resolution"))
    goto free;

  parsedData = extendedFunctions->pfnParseFile(parsedData, token, sizeof(token), 0, nullptr);
  if (!parsedData)
    goto free;

  bitmapBackgroundContext.width = ConvertUtils::fastAToUint<int>(token);

  parsedData = extendedFunctions->pfnParseFile(parsedData, token, sizeof(token), 0, nullptr);
  if (!parsedData)
    goto free;

  bitmapBackgroundContext.height = ConvertUtils::fastAToUint<int>(token);

  // temp variables, will get assign to bitmapBackgroundContext.background arrays only when all of the attr is not invalid
  HIMAGE hImage = 0;
  int offsetX = 0;
  int offsetY = 0;
  unsigned int width = 0;
  unsigned int height = 0;

  bitmapBackgroundContext.backgroundCount = 0;

  while (parsedData = extendedFunctions->pfnParseFile(parsedData, token, sizeof(token), 0, nullptr)) {
    if (!engineFunctions->pfnFileExists(token, gameDirOnly)) {
      mcr_ConsoleDebugLog("%s file doesn't exists", token);
      goto free;
    }

    hImage = engineFunctions->pfnPIC_Load(token, 0, 0, PIC_NOFLIP_TGA);
    if (!hImage)
      goto free;

    // ignore "scaled" attr
    parsedData = extendedFunctions->pfnParseFile(parsedData, token, sizeof(token), 0, nullptr);
    if (!parsedData)
      goto free;

    parsedData = extendedFunctions->pfnParseFile(parsedData, token, sizeof(token), 0, nullptr);
    if (!parsedData)
      goto free;

    offsetX = ConvertUtils::fastAToInt<int>(token);

    parsedData = extendedFunctions->pfnParseFile(parsedData, token, sizeof(token), 0, nullptr);
    if (!parsedData)
      goto free;

    offsetY = ConvertUtils::fastAToInt<int>(token);

    if (bitmapBackgroundContext.backgroundCount >= MAX_BITMAP_BACKGROUND) {
      mcr_ConsoleDebugLog("Max background count reached: %i", MAX_BITMAP_BACKGROUND);
      return false;
    }

    // all required attr is valid, assign to bitmapBackgroundContext.background
    bitmapBackgroundContext.backgroundHImage
      [bitmapBackgroundContext.backgroundCount]
      = hImage;

    bitmapBackgroundContext.backgroundWidth
      [bitmapBackgroundContext.backgroundCount]
      = engineFunctions->pfnPIC_Width(hImage);

    bitmapBackgroundContext.backgroundHeight
      [bitmapBackgroundContext.backgroundCount]
      = engineFunctions->pfnPIC_Height(hImage);

    bitmapBackgroundContext.backgroundX
      [bitmapBackgroundContext.backgroundCount]
      = offsetX;

    bitmapBackgroundContext.backgroundY
      [bitmapBackgroundContext.backgroundCount]
      = offsetY;

    bitmapBackgroundContext.backgroundCount++;
  }

  return true;

free:
  engineFunctions->COM_FreeFile(backgroundLayoutFile);
  return false;
}

bool bitmapBackgroundInitWONBackground(bool gameDirOnly) {
  if (engineFunctions->pfnFileExists(BACKGROUND_SPLASH_WON, gameDirOnly)) { // check if file exists
    HIMAGE hImage = engineFunctions->pfnPIC_Load(BACKGROUND_SPLASH_WON, 0, 0, 0);

    if (!hImage) {
      mcr_ConsoleDebugLog("\"%s\" No such file or directory", BACKGROUND_SPLASH_WON);
      return false;
    }

    return bitmapBackgroundPushBack(
      hImage,
      0,
      0,
      engineFunctions->pfnPIC_Width(hImage),
      engineFunctions->pfnPIC_Height(hImage));
  } else // if file doesnt exist
    return false;
}

bool bitmapBackgroundPushBack(
  HIMAGE hImage,
  int x,
  int y,
  unsigned int width,
  unsigned int height) {

  if (bitmapBackgroundContext.backgroundCount >= MAX_BITMAP_BACKGROUND) {
    mcr_ConsoleDebugLog("Max background count reached: %i", MAX_BITMAP_BACKGROUND);
    return false;
  }

  for (int i = 0; i < MAX_BITMAP_BACKGROUND; i++) {
    if (bitmapBackgroundContext.backgroundHImage[i] == hImage) {
      mcr_ConsoleDebugLog(
        "A background with HIMAGE \"%i\" already exists",
        bitmapBackgroundContext.backgroundHImage[i]);

      return false;
    }
  }

  bitmapBackgroundContext.backgroundHImage
    [bitmapBackgroundContext.backgroundCount]
    = hImage;

  bitmapBackgroundContext.backgroundWidth
    [bitmapBackgroundContext.backgroundCount]
    = width;

  bitmapBackgroundContext.backgroundHeight
    [bitmapBackgroundContext.backgroundCount]
    = height;

  bitmapBackgroundContext.backgroundX
    [bitmapBackgroundContext.backgroundCount]
    = x;

  bitmapBackgroundContext.backgroundY
    [bitmapBackgroundContext.backgroundCount]
    = y;

  bitmapBackgroundContext.backgroundCount++;

  return true;
}

void bitmapBackgroundTransformStyleSwitch() {
  int backgroundWidth = bitmapBackgroundContext.backgroundWidth[bitmapBackgroundContext.background];
  int backgroundHeight = bitmapBackgroundContext.backgroundHeight[bitmapBackgroundContext.background];

  static char backgroundWidthString[8];
  static char backgroundHeightString[8];

  if (cvarMirrors.xashuixyr_background_transform_style.value != BACKGROUND_CUSTOM) {
    ConvertUtils::fastUintToString<int>(backgroundWidthString, backgroundWidth);
    ConvertUtils::fastUintToString<int>(backgroundHeightString, backgroundHeight);

    setCvar(xashuixyr_background_crop_left, "0");
    setCvar(xashuixyr_background_crop_top, "0");
    setCvar(xashuixyr_background_crop_right, backgroundWidthString);
    setCvar(xashuixyr_background_crop_bottom, backgroundHeightString);

    if (cvarMirrors.xashuixyr_background_transform_style.value == BACKGROUND_CENTER) {
      static char backgroundXString[8];
      static char backgroundYString[8];

      ConvertUtils::fastUintToString<int>(backgroundXString, (WINDOW_WIDTH - backgroundWidth) / 2);
      ConvertUtils::fastUintToString<int>(backgroundYString, (WINDOW_HEIGHT - backgroundHeight) / 2);

      setCvar(xashuixyr_background_x, backgroundXString);
      setCvar(xashuixyr_background_y, backgroundYString);

      setCvar(xashuixyr_background_width, backgroundWidthString);
      setCvar(xashuixyr_background_height, backgroundHeightString);
    } else if (cvarMirrors.xashuixyr_background_transform_style.value == BACKGROUND_FIT) {
      float scale = mcr_min(
        static_cast<float>(WINDOW_WIDTH) / backgroundWidth,
        static_cast<float>(WINDOW_HEIGHT) / backgroundHeight);

      static char backgroundXString[8];
      static char backgroundYString[8];

      int backgroundWidthScaled = mcr_floor_positive(backgroundWidth * scale);
      int backgroundHeightScaled = mcr_floor_positive(backgroundHeight * scale);

      ConvertUtils::fastUintToString<int>(backgroundWidthString, backgroundWidthScaled);
      ConvertUtils::fastUintToString<int>(backgroundHeightString, backgroundHeightScaled);

      ConvertUtils::fastUintToString<int>(backgroundXString, (WINDOW_WIDTH - backgroundWidthScaled) / 2);
      ConvertUtils::fastUintToString<int>(backgroundYString, (WINDOW_HEIGHT - backgroundHeightScaled) / 2);

      setCvar(xashuixyr_background_x, backgroundXString);
      setCvar(xashuixyr_background_y, backgroundYString);

      setCvar(xashuixyr_background_width, backgroundWidthString);
      setCvar(xashuixyr_background_height, backgroundHeightString);
    } else if (cvarMirrors.xashuixyr_background_transform_style.value == BACKGROUND_FILL) {
      // TODO: implement fill background transform style
    } else if (cvarMirrors.xashuixyr_background_transform_style.value == BACKGROUND_STRETCH) {
      ConvertUtils::fastUintToString<int>(backgroundWidthString, WINDOW_WIDTH);
      ConvertUtils::fastUintToString<int>(backgroundHeightString, WINDOW_HEIGHT);

      setCvar(xashuixyr_background_x, "0");
      setCvar(xashuixyr_background_y, "0");

      setCvar(xashuixyr_background_width, backgroundWidthString);
      setCvar(xashuixyr_background_height, backgroundHeightString);
    }
  }
}

inline void bitmapBackgroundRender() {
  if (!cvarMirrors.xashuixyr_draw_background.value || (!cvarMirrors.xashuixyr_background_r.value && !cvarMirrors.xashuixyr_background_g.value && !cvarMirrors.xashuixyr_background_b.value) || !cvarMirrors.xashuixyr_background_a.value)
    return;

  static wrect_t bitmapBackgroundRect;

  bitmapBackgroundRect.left = cvarMirrors.xashuixyr_background_crop_left.value;
  bitmapBackgroundRect.top = cvarMirrors.xashuixyr_background_crop_top.value;

  bitmapBackgroundRect.right = cvarMirrors.xashuixyr_background_crop_right.value;
  bitmapBackgroundRect.bottom = cvarMirrors.xashuixyr_background_crop_bottom.value;

  // use first background for now
  // TODO: backgrounder switcher

  engineFunctions->pfnPIC_Set(
    bitmapBackgroundContext.backgroundHImage[bitmapBackgroundContext.background],
    cvarMirrors.xashuixyr_background_r.value,
    cvarMirrors.xashuixyr_background_g.value,
    cvarMirrors.xashuixyr_background_b.value,
    cvarMirrors.xashuixyr_background_a.value);

  engineFunctions->pfnPIC_Draw(
    cvarMirrors.xashuixyr_background_x.value,
    cvarMirrors.xashuixyr_background_y.value,
    cvarMirrors.xashuixyr_background_width.value,
    cvarMirrors.xashuixyr_background_height.value,
    &bitmapBackgroundRect);
}

inline void bitmapBackgroundFree(void) {
  bitmapBackgroundContext.width = 0;
  bitmapBackgroundContext.height = 0;
  bitmapBackgroundContext.background = 0;
}

void bitmapBackgroundInit(BackgroundSrcEnums backgroundSrc) {
  bitmapBackgroundFree();

  if (backgroundSrc == BACKGROUND_SRC_STEAM) {
    if (bitmapBackgroundInitSteamBackground(true, true))
      mcr_ConsoleDebugLog("found background \"%s\" in \"%s\"", "steam", "game/");
    else if (bitmapBackgroundInitSteamBackground(true, false))
      mcr_ConsoleDebugLog("found background \"%s\" in \"%s\"", "steam", "base/");
  } else if (backgroundSrc == BACKGROUND_SRC_WON) {
    if (bitmapBackgroundInitWONBackground(true))
      mcr_ConsoleDebugLog("found background \"%s\" in \"%s\"", BACKGROUND_SPLASH_WON, "game/");
    else if (bitmapBackgroundInitWONBackground(false))
      mcr_ConsoleDebugLog("found background \"%s\" in \"%s\"", BACKGROUND_SPLASH_WON, "game/");
  }

  bitmapBackgroundContext.backgroundSrc = backgroundSrc;
  mcr_ConsoleDebugLog("Background count: %i", bitmapBackgroundContext.backgroundCount);
}

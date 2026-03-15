
#include "Base.h"
#include "Cvars/Cvars.h"
#include "Commands.h"
#include "Tricks.h"
#include "Managers/Background/Background.h"
#include "Managers/Font/Font.h"

#include "Primitives/Key.h"
#include "Primitives/Transform.h"

#include "Menus/MenusExport.h"
#include "Menus/UpdateElement.h"

#include "Utils/CursorUtils.h"
#include "Utils/ConvertUtils.h"
#include "Utils/Utils.h"

UIContext globalUIContext;
UIMouseContext globalUIMouseContext;
UIKeyContext globalUIKeyContext;

void fillPackedRGBA(int x, int y, int width, int height, unsigned int rgba) {
  engineFunctions->pfnFillRGBA(
    x, y,
    width, height,
    (rgba >> 24) & 0xFF,
    (rgba >> 16) & 0xFF,
    (rgba >> 8) & 0xFF,
    rgba & 0xFF);
}

void mouseEventsLog() {
  mcr_ConsoleDebugLog(
    "mouseDown: %i, lastMouseDown: %i, mouseMove: %i, lastMouseMove: %i, mouseDouble: %i",
    globalUIMouseContext.mouseDown,
    globalUIMouseContext.lastMouseDown,
    globalUIMouseContext.mouseMove,
    globalUIMouseContext.lastMouseMove,
    globalUIMouseContext.mouseDouble);
}

void mouseEventsReset() {
  globalUIMouseContext.mouseDown = false;
  globalUIMouseContext.lastMouseDown = false;

  globalUIMouseContext.mouseMove = false;
  globalUIMouseContext.lastMouseMove = false;

  globalUIMouseContext.mouseDouble = false;
}

void switchMenu(MenuEnums menu) {
  globalUIContext.menu = menu;

  // do something here?
}

void navigateToMenu(MenuEnums menu) {
  globalUIContext.menu = menu;
  globalUIContext.menusHistory[globalUIContext.menusHistoryCount] = menu;
  globalUIContext.menusHistoryCount++;

  if (menu == MENU_NULL)
    ;
  else if (menu == MENU_MAIN)
    ;
  else if (menu == MENU_SETTINGS)
    ;

  updateUIDisplayDimensionAndShifts();
  elementsShiftsAndScaleUpdate();
}

void goBackToLastMenu() {
  globalUIContext.menu = globalUIContext.menusHistory[globalUIContext.menusHistoryCount - 2];
  globalUIContext.menusHistoryCount--;
  globalUIContext.menusHistory[globalUIContext.menusHistoryCount] = MENU_NULL;

  updateUIDisplayDimensionAndShifts();
  elementsShiftsAndScaleUpdate();
}

inline void setKeyDestWrapper(KeyDestEnums keyDest) {
  globalUIContext.keyDest = keyDest;
  engineFunctions->pfnSetKeyDest(keyDest);
}

// update display dimension to scale menus' elements to fit the window
void updateUIDisplayDimensionAndShifts() {
  long long windowWidth = globalUIContext.windowWidth;
  long long windowHeight = globalUIContext.windowHeight;

  if (windowWidth * UI_TARGET_ASPECT_HEIGHT > windowHeight * UI_TARGET_ASPECT_WIDTH) {
    globalUIContext.displayWidth = windowHeight * UI_TARGET_ASPECT_WIDTH / UI_TARGET_ASPECT_HEIGHT;
    globalUIContext.displayHeight = windowHeight;
  } else {
    globalUIContext.displayWidth = windowWidth;
    globalUIContext.displayHeight = windowWidth * UI_TARGET_ASPECT_HEIGHT / UI_TARGET_ASPECT_WIDTH;
  }

  globalUIContext.shiftX = (windowWidth - globalUIContext.displayWidth) / 2;
  globalUIContext.shiftY = (windowHeight - globalUIContext.displayHeight) / 2;
}

GAME_EXPORT void _mouseMove(int x, int y) {
  if (globalTricks.mouseMoveGeneration >= globalTricks.lastProcessedMouseMoveGen) {
    mouseEventsReset();
    elementMouseEventsReset();
  }

  if (globalUIMouseContext.cursorX == x && globalUIMouseContext.cursorY == y) {
    globalTricks.mouseMoveGeneration++;
    return;
  }

  globalUIMouseContext.mouseInWindow = CursorUtils::isMouseInRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, x, y);

  globalUIMouseContext.cursorX = x;
  globalUIMouseContext.cursorY = y;

  globalUIMouseContext.mouseMove = true;

  elementMouseEventsController();

  globalTricks.mouseMoveGeneration++;
}

// called every frame, stop calling when engine's key dest is console
void updateUI() {
  if (globalTricks.mouseMoveGeneration > globalTricks.lastProcessedMouseMoveGen)
    globalTricks.lastProcessedMouseMoveGen = globalTricks.mouseMoveGeneration;

  if (!globalUIContext.processNextFrame) // only update when processNextFrame is true
    return;

  globalUIMouseContext.lastMouseDown = globalUIMouseContext.mouseDown;
  globalUIMouseContext.lastMouseMove = globalUIMouseContext.mouseMove;

  syncCvarMirrors();        // sync cvars
  bitmapBackgroundRender(); // render background
  elementCvarSync();        // sync UIElementExtensionCvar to cvar

  if (globalUIKeyContext.keyDown)
    globalUIContext.ptrToMenuContainers[globalUIContext.menu]->keyDownMenu(globalUIKeyContext.keyCode);

  (*globalUIContext.ptrToMenusRenderFunction[globalUIContext.menu])();

  char buffer[8];
  ConvertUtils::fastUintToString<int>(buffer, globalUIContext.fps);
  engineFunctions->pfnDrawConsoleString(0, 0, buffer);

  globalTricks.lastProcessedMouseMoveGen++;
}

inline void uiContextMenusInit() {
  globalUIContext.ptrToMenusRenderFunction[MENU_NULL] = nullptr;
  globalUIContext.ptrToMenusRenderFunction[MENU_MAIN] = &menuMainRenderWrapper;
  globalUIContext.ptrToMenusRenderFunction[MENU_SETTINGS] = &menuSettingsRenderWrapper;
  globalUIContext.ptrToMenusRenderFunction[MENU_SETTINGS_CONTROLS] = &menuSettingsControlsRenderWrapper;
  globalUIContext.ptrToMenusRenderFunction[MENU_SETTINGS_ADV_CONTROLS] = &menuSettingsAdvControlsRenderWrapper;
  globalUIContext.ptrToMenusRenderFunction[MENU_SETTINGS_AUDIO] = &menuSettingsAudioRenderWrapper;

  globalUIContext.ptrToMenuContainers[MENU_NULL] = nullptr;
  globalUIContext.ptrToMenuContainers[MENU_MAIN] = &menuMain;
  globalUIContext.ptrToMenuContainers[MENU_SETTINGS] = &menuSettings;
  globalUIContext.ptrToMenuContainers[MENU_SETTINGS_CONTROLS] = &menuSettingsControls;
  globalUIContext.ptrToMenuContainers[MENU_SETTINGS_ADV_CONTROLS] = &menuSettingsAdvControls;
  globalUIContext.ptrToMenuContainers[MENU_SETTINGS_AUDIO] = &menuSettingsAudio;

  globalUIContext.menusHistoryCount = 0;

  globalUIContext.processNextFrame = true;
}

inline void uiMouseContextInit() {
  globalUIMouseContext.cursorX = 0;
  globalUIMouseContext.cursorY = 0;

  globalUIMouseContext.mouseDown = false;
  globalUIMouseContext.lastMouseDown = false;

  globalUIMouseContext.mouseMove = false;
  globalUIMouseContext.lastMouseMove = false;

  globalUIMouseContext.mouseDouble = false;
}

// baseVideoInit gets called after baseInit
GAME_EXPORT int _baseVideoInit(void) {
  globalUIContext.windowWidth = WINDOW_WIDTH;
  globalUIContext.windowHeight = WINDOW_HEIGHT;

  globalUIContext.baseWidth = UI_BASE_WIDTH;
  globalUIContext.baseHeight = UI_BASE_HEIGHT;

  bitmapFontInit(FONT_BUILTIN); // init bitmap font(currently builtin font)
  bitmapBackgroundTransformStyleSwitch();

  updateUIDisplayDimensionAndShifts();
  elementsShiftsAndScaleUpdate();

  mcr_ConsoleDebugLog("window dimension: %ix%i", globalUIContext.windowWidth, globalUIContext.windowHeight);
  mcr_ConsoleDebugLog("display dimension: %ix%i", globalUIContext.displayWidth, globalUIContext.displayHeight);
  mcr_ConsoleDebugLog("shifts: x: %i, y: %i", globalUIContext.shiftX, globalUIContext.shiftY);

  return 1;
}

GAME_EXPORT void _baseInit(void) {
  // avoid divide by 0
  globalUIContext.baseWidth = 1;
  globalUIContext.baseHeight = 1;

  uiContextMenusInit();
  cvarsInit();
  commandsInit();

  // setup game info
  static gameinfo2_t *gameInfo = extendedFunctions->pfnGetGameInfo(GAMEINFO_VERSION);
  if (!gameInfo)
    engineFunctions->pfnHostError(
      "From menu.dll: pfnGetGameInfo returned NULL\nGAMEINFO_VERSION: %i",
      GAMEINFO_VERSION);

  globalGameInfo = gameInfo;

  navigateToMenu(MENU_MAIN); // starts at main menu
  setKeyDestWrapper(KEY_MENU);

  bitmapBackgroundInit(BACKGROUND_SRC_WON);

  static char cropRight[8];
  ConvertUtils::fastIntToString<int>(cropRight, bitmapBackgroundContext.backgroundWidth[bitmapBackgroundContext.background]);
  xashuixyr_background_crop_right->string = cropRight;

  static char cropBottom[8];
  ConvertUtils::fastIntToString<int>(cropBottom, bitmapBackgroundContext.backgroundHeight[bitmapBackgroundContext.background]);
  xashuixyr_background_crop_bottom->string = cropBottom;

  menuMainInit();
  menuSettingsInit();
  menuSettingsControlsInit();
  menuSettingsAudioInit();

  globalUIContext.initialized = true;

  mcr_ConsoleDebugLog("addtional cvars:");

  mcr_ConsoleDebugLog("  %s", xashuixyr_base_width->name);
  mcr_ConsoleDebugLog("  %s", xashuixyr_base_height->name);

  mcr_ConsoleDebugLog("  %s", xashuixyr_draw_background->name);

  mcr_ConsoleDebugLog("  %s", xashuixyr_background_r->name);
  mcr_ConsoleDebugLog("  %s", xashuixyr_background_g->name);
  mcr_ConsoleDebugLog("  %s", xashuixyr_background_b->name);
  mcr_ConsoleDebugLog("  %s", xashuixyr_background_a->name);

  mcr_ConsoleDebugLog("  %s", xashuixyr_background_x->name);
  mcr_ConsoleDebugLog("  %s", xashuixyr_background_y->name);
  mcr_ConsoleDebugLog("  %s", xashuixyr_background_width->name);
  mcr_ConsoleDebugLog("  %s", xashuixyr_background_height->name);

  mcr_ConsoleDebugLog("  %s", xashuixyr_background_crop_left->name);
  mcr_ConsoleDebugLog("  %s", xashuixyr_background_crop_top->name);
  mcr_ConsoleDebugLog("  %s", xashuixyr_background_crop_right->name);
  mcr_ConsoleDebugLog("  %s", xashuixyr_background_crop_bottom->name);

  mcr_ConsoleDebugLog("  %s", xashuixyr_bound_x->name);
  mcr_ConsoleDebugLog("  %s", xashuixyr_bound_y->name);

  mcr_ConsoleDebugLog("  %s", xashuixyr_font->name);

  mcr_ConsoleDebugLog("initialized UI");
}

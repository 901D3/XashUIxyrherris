
#include "FUNCTION_EXPORTING.h"
#include "Base.h"
#include "Commands.h"

#include "Menus/UpdateElement.h"

#include "Primitives/Key.h"
#include "Primitives/Transform.h"

#include "Utils/CursorUtils.h"
#include "Utils/MathUtils.h"
#include "Utils/Utils.h"

// UI_FUNCTIONS
void UI_Shutdown() {
}

void UI_UpdateMenu(float flTime) {
  globalUIContext.fps = 1 / (flTime - globalUIContext.uiTimeF);

  globalUIContext.uiTime = static_cast<int>(flTime * 1000.f); // update time
  globalUIContext.uiTimeF = flTime;                           // update float time

  updateUI();
}

// down = 1: single key, down = 2: double key
void UI_KeyEvent(int key, int down) {
  if (!globalUIContext.initialized)
    return;

  globalUIKeyContext.keyCode = key;
  globalUIKeyContext.keyDown = down;

  if (key == K_MOUSE1) {
    globalUIMouseContext.mouseDown = !!down;
    elementMouseEventsController();
  }

  // if (key == K_ESCAPE);
  // if (globalUIContext.keyDest == KEY_MENU);
}

void UI_MouseMove(int x, int y) {
  mouseMove(x, y);
};

void UI_SetActiveMenu(int active) {
  if (!globalUIContext.initialized)
    return;

  engineFunctions->pfnKeyClearStates();

  if (active) {
    engineFunctions->pfnSetKeyDest(KEY_MENU);
    globalUIContext.processNextFrame = true;
  } else {
    engineFunctions->pfnSetKeyDest(KEY_GAME);
    globalUIContext.processNextFrame = false;
  }
}

void UI_AddServerToList(netadr_s adr, const char *info) {
  if (!globalUIContext.initialized)
    return;
}

void UI_GetCursorPos(int *pos_x, int *pos_y) {
  if (!globalUIContext.initialized)
    return;

  *pos_x = globalUIMouseContext.cursorX;
  *pos_y = globalUIMouseContext.cursorY;
}

void UI_SetCursorPos(int pos_x, int pos_y) {
  if (!globalUIContext.initialized)
    return;

  globalUIMouseContext.cursorX = pos_x;
  globalUIMouseContext.cursorY = pos_y;
}

void UI_ShowCursor(int show) {
  if (!globalUIContext.initialized)
    return;

  globalUIMouseContext.showCursor = show ? true : false;
}

void UI_CharEvent(int key) {
  if (!globalUIContext.initialized)
    return;
}

int UI_MouseInRect() {
  return static_cast<bool>(globalUIMouseContext.mouseInWindow);
}

int UI_IsVisible() {
  return static_cast<bool>(globalUIContext.processNextFrame);
}

int UI_CreditsActive() {
  return 0;
}

void UI_FinalCredits() {
}

// UI_EXTENDED_FUNCTIONS
void AddTouchButtonToList(
  const char *name,
  const char *texture,
  const char *command,
  unsigned char *color,
  int flags) {
}

void UI_MenuResetPing_f() {
}

void UI_ConnectionWarning_f() {
}

void UI_UpdateDialog(int preferStore) {
}

void UI_ShowMessageBox(const char *text) {
}

void UI_ConnectionProgress_Disconnect() {
}

void UI_ConnectionProgress_Download(
  const char *pszFileName,
  const char *pszServerName,
  int iCurrent,
  int iTotal,
  const char *comment) {
}

void UI_ConnectionProgress_DownloadEnd() {
}

void UI_ConnectionProgress_Precache() {
}

void UI_ConnectionProgress_Connect(const char *server) {
}

void UI_ConnectionProgress_ChangeLevel() {
}

void UI_ConnectionProgress_ParseServerInfo(const char *server) {
}

/**
 * UIDefs.h - UI definitions
 */

#pragma once

#include "Primitives/Function.h" // PtrToVoidFunction

#include "XashEngineRelated/XashKey.h"

#include "Menus/MenuDefs.h" // MenuEnums
#include "Menus/MenuBase.h" // UIMenu

#define CURRENT_MENU (globalUIContext.ptrToMenuContainers[globalUIContext.menu])

// TODO: document this
typedef struct {
  int uiTime; // ms
  float uiTimeF;
  int fps;

  // window dimension
  int windowWidth;
  int windowHeight;

  // width and height for menus and elements
  int baseWidth;
  int baseHeight;

  int displayWidth;
  int displayHeight;

  // elements position shift
  int shiftX;
  int shiftY;

  bool initialized;
  bool processNextFrame;
  bool textInput;

  KeyDestEnums keyDest;

  MenuEnums menu;

  PtrToVoidFunction ptrToMenusRenderFunction[MENU_COUNT];
  UIMenu *ptrToMenuContainers[MENU_COUNT];
  MenuEnums menusHistory[MENU_COUNT]; // allows MENU_COUNT menu history
  int menusHistoryCount;

} UIContext;

// cursor stuff, key id
typedef struct {
  int cursorX;
  int cursorY;

  bool mouseInWindow;
  bool showCursor;

  bool mouseDown;
  bool lastMouseDown;

  bool mouseMove;
  bool lastMouseMove;

  bool mouseDouble; // double click

} UIMouseContext;

// key stuff
typedef struct {
  int keyCode;
  int keyDown; // for any key, including mouse keys

} UIKeyContext;

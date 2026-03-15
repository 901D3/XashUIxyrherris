
#pragma once

#include "keydefs.h"

namespace KeyUtils {

  inline bool isEscape(int key) {
    return key == K_ESCAPE;
  }

  inline bool isEnter(int key) {
    return key == K_ENTER;
  }

  inline bool isBackspace(int key) {
    return key == K_BACKSPACE;
  }

  inline bool isHome(int key) {
    return key == K_HOME;
  }

  inline bool isEnd(int key) {
    return key == K_END;
  }

  inline bool isMouseKeys(int key) {
    return (
      key == K_MOUSE1
      || key == K_MOUSE2
      || key == K_MOUSE3
      || key == K_MOUSE4
      || key == K_MOUSE5);
  }

  inline bool isLeftMouse(int key) {
    return key == K_MOUSE1;
  }

  inline bool isUpArrow(int key) {
    return key == K_KP_UPARROW;
  }

  inline bool isLeftArrow(int key) {
    return key == K_KP_LEFTARROW;
  }

  inline bool isRightArrow(int key) {
    return key == K_KP_RIGHTARROW;
  }

  inline bool isDownArrow(int key) {
    return key == K_KP_DOWNARROW;
  }

  inline bool isNavigationKeys(int key) {
    return (
      key == K_KP_UPARROW
      || key == K_KP_LEFTARROW
      || key == K_KP_RIGHTARROW
      || key == K_KP_DOWNARROW
      || key == K_TAB);
  }

  inline bool isPageUp(int key) {
    return key == K_PGUP;
  }

  inline bool isPageDown(int key) {
    return key == K_PGDN;
  }

  inline bool isConsoleKey(int key) {
    return (key == '`' || key == '~');
  }

  inline bool isAlphaNumericKeys(int key) {
    return (key >= '0' && key <= '9') || (key >= 'a' && key <= 'z');
  }

} // namespace KeyUtils

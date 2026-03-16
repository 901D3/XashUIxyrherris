
#pragma once

#include "Primitives/Transform.h"
#include "Primitives/Function.h"
#include "Primitives/Color.h"

#include <string> // std::string

#include "Elements/ElementDefs.h"

// TODO: document this
class UIElement {
public:
  UIElement();
  virtual ~UIElement();

  ElementEnums elementID;

  // style
  unsigned int backgroundColor;
  unsigned int backgroundColorMouseHover;
  unsigned int backgroundColorMouseHold;
  unsigned int backgroundColorDisabled;

  unsigned int borderColor;
  unsigned int borderColorMouseHover;
  unsigned int borderColorMouseHold;
  unsigned int borderColorDisabled;

  int borderLeftWidth;
  int borderTopWidth;
  int borderRightWidth;
  int borderBottomWidth;

  int scaledBorderLeftWidth;
  int scaledBorderTopWidth;
  int scaledBorderRightWidth;
  int scaledBorderBottomWidth;

  bool visible;
  bool lastVisible;
  bool background;
  bool border;
  bool additiveBlend;

  BorderSides borderSides;

  // transform
  int x;
  int y;
  int width;
  int height;

  int shiftedX;
  int shiftedY;
  int scaledWidth;
  int scaledHeight;

  // id
  std::string identifier;

  // behaviour
  bool enabled;
  bool lastEnabled;

  bool focus;
  bool lastFocus;

  bool mouseHover;
  bool lastMouseHover;

  bool mouseDown;
  bool lastMouseDown;

  PtrToVoidFunction onDisable;
  PtrToVoidFunction onEnable;

  PtrToVoidFunction onInvisible;
  PtrToVoidFunction onVisible;

  PtrToVoidFunction onGotFocus;  // when got focus
  PtrToVoidFunction onFocus;     // get called continuously
  PtrToVoidFunction onLostFocus; // when unfocus

  PtrToVoidFunction onMouseHoverIn;  // when mouse hovered in
  PtrToVoidFunction onMouseHover;    // get called continuously
  PtrToVoidFunction onMouseHoverOut; // when mouse hovered out

  PtrToVoidFunction onMouseDown; // when mouse just pressed
  PtrToVoidFunction onMouseHold; // get called continuously
  PtrToVoidFunction onMouseUp;   // when mouse released

  // styling functions
  virtual void drawBackground();
  virtual void drawBackgroundMouseHover();
  virtual void drawBackgroundMouseHold();
  virtual void drawBackgroundDisabled();

  virtual void drawBorder();
  virtual void drawBorderMouseHover();
  virtual void drawBorderMouseHold();
  virtual void drawBorderDisabled();

  // transform functions
  // position functions that applies UI's position shift
  virtual void setX(int x);
  virtual void setY(int y);
  virtual void setPosition(int x, int y);
  virtual void updateShiftedPosition();

  // dimension functions that applies UI's scale
  virtual void setWidth(int width);
  virtual void setHeight(int height);
  virtual void setDimension(int width, int height);
  virtual void updateScaledDimension();

  // borders' width too
  virtual void updateScaledBorderWidth();

  // behaviour functions
  virtual void setVisible(bool visible); // preferred
  virtual void setEnabled(bool enabled); // preferred

  virtual void keyDown(int key); // will be modified by a custom element

  // render() is called during screen(and UI) update, usually UI_UpdateMenu() -> updateUI()
  virtual void render(); // will be modified by a custom element
};

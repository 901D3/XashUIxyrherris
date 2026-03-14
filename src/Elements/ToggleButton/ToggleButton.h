
#pragma once

#include "Base.h"
#include "Elements/ElementExtensions/ElementExtensionCvar.h"
#include "Primitives/Function.h"

class UIElementToggleButton
    : public UIElement,
      public UIElementExtensionCvar {
public:
  UIElementToggleButton();
  virtual ~UIElementToggleButton();

  unsigned int backgroundColorToggleTrue;
  unsigned int borderColorToggleTrue;

  bool toggle;

  FunctionWithClassInstance onMouseUpBuiltIn;

  void mouseUp();

  virtual void drawBackgroundToggleTrue();
  virtual void drawBorderToggleTrue();

  void render(); // modify UIElement's render()
};

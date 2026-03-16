
#pragma once

#include "Primitives/Function.h"

#include "Base.h"
#include "Elements/ElementExtensions/ElementExtensionCvar.h"

class UIElementToggleButton
    : public UIElement,
      public UIElementExtensionCvar {
public:
  UIElementToggleButton();
  virtual ~UIElementToggleButton();

  unsigned int backgroundColorToggleTrue;
  unsigned int borderColorToggleTrue;

  bool toggle;

  // must be called when defining onMouseUp for this element, otherwise use a custom logic
  virtual void toggleHelper();

  virtual void drawBackgroundToggleTrue();
  virtual void drawBorderToggleTrue();

  void render(); // modify UIElement's render()
};


#pragma once

// dynamic string
#include <string>

#include "Base.h"
#include "Elements/ElementBase.h"

#include "Managers/Font/Font.h"

class UIElementText : public UIElement {
public:
  std::string text;

  unsigned int textColor;
  unsigned int textColorMouseHover;
  unsigned int textColorMouseHold;
  unsigned int textColorDisabled;

  float widthScale;
  float heightScale;

  bool autoWrap;
  bool widthClip;
  bool heightClip;

  // css's "fit-content" equivalent
  bool widthFitContent;
  bool heightFitContent;

  bool useConsoleFont;

  UIElementText();
  virtual ~UIElementText();

  void render(); // modify UIElement's render()
};


#include "Primitives/Color.h"

#include "Base.h"
#include "Elements/ToggleButton/ToggleButton.h"

#include "Presets/PresetsColor.h"

#include "ProjectUtils/Utils.h"
#include "Utils/ConvertUtils.h"
#include "Utils/ColorUtils.h"
#include "Utils/MathUtils.h"

UIElementToggleButton::UIElementToggleButton() {
  UIElement::elementID = ELEMENT_TOGGLE_BUTTON;

  UIElement::backgroundColor = 0x777777AE;
  UIElement::borderColor = ColorUtils::packRGBAFromStruct(&presetColorOrange2MouseHold);

  UIElement::background = true;
  UIElement::border = true;
  UIElement::width = 24;
  UIElement::height = 24;

  toggle = false;

  backgroundColorToggleTrue = ColorUtils::packRGBAFromStruct(&presetColorOrange2);
  borderColorToggleTrue = ColorUtils::packRGBAFromStruct(&presetColorOrange2MouseHover);
}

UIElementToggleButton::~UIElementToggleButton() {
}

void UIElementToggleButton::toggleHelper() {
  toggle = !toggle;

  if (UIElementExtensionCvar::cvar) {
    const char string[2] = {'0' + static_cast<bool>(toggle), 0};
    UIElementExtensionCvar::setCvarString(string);
  }
}

inline void UIElementToggleButton::drawBackgroundToggleTrue() {
  if (backgroundColorToggleTrue == 0)
    return;

  fillPackedRGBA(
    shiftedX, shiftedY,
    scaledWidth, scaledHeight,
    backgroundColorToggleTrue);
}

inline void UIElementToggleButton::drawBorderToggleTrue() {
  if (borderSides & BORDER_LEFT && scaledBorderLeftWidth)
    fillPackedRGBA(
      UIElement::shiftedX, UIElement::shiftedY + UIElement::scaledBorderTopWidth,
      UIElement::scaledBorderLeftWidth, UIElement::scaledHeight - UIElement::scaledBorderBottomWidth * 2,
      borderColorToggleTrue);

  if (borderSides & BORDER_TOP && scaledBorderTopWidth)
    fillPackedRGBA(
      UIElement::shiftedX, UIElement::shiftedY,
      UIElement::scaledWidth, UIElement::scaledBorderTopWidth,
      borderColorToggleTrue);

  if (borderSides & BORDER_RIGHT && scaledBorderRightWidth)
    fillPackedRGBA(
      UIElement::shiftedX + UIElement::scaledWidth - UIElement::scaledBorderRightWidth, UIElement::shiftedY + UIElement::scaledBorderTopWidth,
      UIElement::scaledBorderRightWidth, UIElement::scaledHeight - UIElement::scaledBorderBottomWidth * 2,
      borderColorToggleTrue);

  if (borderSides & BORDER_BOTTOM && scaledBorderBottomWidth)
    fillPackedRGBA(
      UIElement::shiftedX, UIElement::shiftedY + UIElement::scaledHeight - UIElement::scaledBorderBottomWidth,
      UIElement::scaledWidth, UIElement::scaledBorderBottomWidth,
      borderColorToggleTrue);
}

void UIElementToggleButton::render() {
  if (!UIElement::visible || !UIElement::width || !UIElement::height)
    return;

  if (UIElement::background) {
    if (!UIElement::enabled)
      UIElement::drawBackgroundDisabled();
    else if (UIElement::mouseHover && !UIElement::mouseDown)
      UIElement::drawBackgroundMouseHover();
    else if (UIElement::mouseDown || toggle)
      drawBackgroundToggleTrue();
    else
      UIElement::drawBackground();
  }

  if (UIElement::border) {
    if (!UIElement::enabled)
      UIElement::drawBorderDisabled();
    else if (UIElement::mouseHover && !UIElement::mouseDown)
      UIElement::drawBorderMouseHover();
    else if (UIElement::mouseDown || toggle)
      drawBorderToggleTrue();
    else
      UIElement::drawBorder();
  }
}

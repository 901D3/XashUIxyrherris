
#include "Base.h"
#include "EngineStuff.h"
#include "Elements/ElementBase.h"

#include "Presets/PresetsColor.h"
#include "Presets/PresetsBorder.h"

#include "Utils/TransformUtils.h"
#include "Utils/ColorUtils.h"
#include "Utils/Utils.h"

UIElement::UIElement() {
  elementID = ELEMENT_BASE;

  // style
  backgroundColor = ColorUtils::packRGBAFromStruct(&presetColorDarkerOrange);
  backgroundColorMouseHover = ColorUtils::packRGBAFromStruct(&presetColorGrayMouseHover);
  backgroundColorMouseHold = ColorUtils::packRGBAFromStruct(&presetColorOrange2MouseHold);
  backgroundColorDisabled = ColorUtils::packRGBAFromStruct(&presetColorGrayDisabled);

  borderColor = ColorUtils::packRGBAFromStruct(&presetColorDarkOrange);
  borderColorMouseHover = ColorUtils::packRGBAFromStruct(&presetColorOrange2MouseHover);
  borderColorMouseHold = ColorUtils::packRGBAFromStruct(&presetColorGrayMouseHold);
  borderColorDisabled = ColorUtils::packRGBAFromStruct(&presetColorGrayDisabled);

  borderLeftWidth = 2;
  borderTopWidth = 2;
  borderRightWidth = 2;
  borderBottomWidth = 2;

  scaledBorderLeftWidth = 2;
  scaledBorderTopWidth = 2;
  scaledBorderRightWidth = 2;
  scaledBorderBottomWidth = 2;

  enabled = true;
  visible = true;
  background = border = false;
  borderSides = BORDER_ALL;

  // transform
  x = 0;
  y = 0;
  width = 0;
  height = 0;
  shiftedX = 0;
  shiftedY = 0;
  scaledWidth = 0;
  scaledHeight = 0;

  // behaviour
  focus = false;
  lastFocus = false;
  mouseHover = false;
  lastMouseHover = false;
  mouseDown = false;
  lastMouseDown = false;

  onDisable = &dummyFunction;
  onEnable = &dummyFunction;
  onInvisible = &dummyFunction;
  onVisible = &dummyFunction;
  onGotFocus = &dummyFunction;
  onFocus = &dummyFunction;
  onLostFocus = &dummyFunction;
  onMouseHoverIn = &dummyFunction;
  onMouseHover = &dummyFunction;
  onMouseHoverOut = &dummyFunction;
  onMouseDown = &dummyFunction;
  onMouseHold = &dummyFunction;
  onMouseUp = &dummyFunction;
}

UIElement::~UIElement() {
}

inline void UIElement::drawBackground() {
  if (backgroundColor == 0)
    return;

  fillPackedRGBA(shiftedX, shiftedY,
    scaledWidth, scaledHeight,
    backgroundColor);
}

inline void UIElement::drawBackgroundMouseHover() {
  if (backgroundColorMouseHover == 0)
    return;

  fillPackedRGBA(
    shiftedX, shiftedY,
    scaledWidth, scaledHeight,
    backgroundColorMouseHover);
}

inline void UIElement::drawBackgroundMouseHold() {
  if (backgroundColorMouseHold == 0)
    return;

  fillPackedRGBA(
    shiftedX, shiftedY,
    scaledWidth, scaledHeight,
    backgroundColorMouseHold);
}

inline void UIElement::drawBackgroundDisabled() {
  if (backgroundColorDisabled == 0)
    return;

  fillPackedRGBA(
    shiftedX, shiftedY,
    scaledWidth, scaledHeight,
    backgroundColorDisabled);
}

inline void UIElement::drawBorder() {
  if (borderSides & BORDER_LEFT && scaledBorderLeftWidth)
    fillPackedRGBA(
      shiftedX, shiftedY + scaledBorderTopWidth,
      scaledBorderLeftWidth, scaledHeight - scaledBorderBottomWidth * 2,
      borderColor);

  if (borderSides & BORDER_TOP && scaledBorderTopWidth)
    fillPackedRGBA(
      shiftedX, shiftedY,
      scaledWidth, scaledBorderTopWidth,
      borderColor);

  if (borderSides & BORDER_RIGHT && scaledBorderRightWidth)
    fillPackedRGBA(
      shiftedX + scaledWidth - scaledBorderRightWidth, shiftedY + scaledBorderTopWidth,
      scaledBorderRightWidth, scaledHeight - scaledBorderBottomWidth * 2,
      borderColor);

  if (borderSides & BORDER_BOTTOM && scaledBorderBottomWidth)
    fillPackedRGBA(
      shiftedX, shiftedY + scaledHeight - scaledBorderBottomWidth,
      scaledWidth, scaledBorderBottomWidth,
      borderColor);
}

inline void UIElement::drawBorderMouseHover() {
  if (borderSides & BORDER_LEFT && scaledBorderLeftWidth)
    fillPackedRGBA(
      shiftedX, shiftedY + scaledBorderTopWidth,
      scaledBorderLeftWidth, scaledHeight - scaledBorderBottomWidth * 2,
      borderColorMouseHover);

  if (borderSides & BORDER_TOP && scaledBorderTopWidth)
    fillPackedRGBA(
      shiftedX, shiftedY,
      scaledWidth, scaledBorderTopWidth,
      borderColorMouseHover);

  if (borderSides & BORDER_RIGHT && scaledBorderRightWidth)
    fillPackedRGBA(
      shiftedX + scaledWidth - scaledBorderRightWidth, shiftedY + scaledBorderTopWidth,
      scaledBorderRightWidth, scaledHeight - scaledBorderBottomWidth * 2,
      borderColorMouseHover);

  if (borderSides & BORDER_BOTTOM && scaledBorderBottomWidth)
    fillPackedRGBA(
      shiftedX, shiftedY + scaledHeight - scaledBorderBottomWidth,
      scaledWidth, scaledBorderBottomWidth,
      borderColorMouseHover);
}

inline void UIElement::drawBorderMouseHold() {
  if (borderSides & BORDER_LEFT && scaledBorderLeftWidth)
    fillPackedRGBA(
      shiftedX, shiftedY + scaledBorderTopWidth,
      scaledBorderLeftWidth, scaledHeight - scaledBorderBottomWidth * 2,
      borderColorMouseHold);

  if (borderSides & BORDER_TOP && scaledBorderTopWidth)
    fillPackedRGBA(
      shiftedX, shiftedY,
      scaledWidth, scaledBorderTopWidth,
      borderColorMouseHold);

  if (borderSides & BORDER_RIGHT && scaledBorderRightWidth)
    fillPackedRGBA(
      shiftedX + scaledWidth - scaledBorderRightWidth, shiftedY + scaledBorderTopWidth,
      scaledBorderRightWidth, scaledHeight - scaledBorderBottomWidth * 2,
      borderColorMouseHold);

  if (borderSides & BORDER_BOTTOM && scaledBorderBottomWidth)
    fillPackedRGBA(
      shiftedX, shiftedY + scaledHeight - scaledBorderBottomWidth,
      scaledWidth, scaledBorderBottomWidth,
      borderColorMouseHold);
}

inline void UIElement::drawBorderDisabled() {
  if (borderSides & BORDER_LEFT && scaledBorderLeftWidth)
    fillPackedRGBA(
      shiftedX, shiftedY + scaledBorderTopWidth,
      scaledBorderLeftWidth, scaledHeight - scaledBorderBottomWidth * 2,
      borderColorDisabled);

  if (borderSides & BORDER_TOP && scaledBorderTopWidth)
    fillPackedRGBA(
      shiftedX, shiftedY,
      scaledWidth, scaledBorderTopWidth,
      borderColorDisabled);

  if (borderSides & BORDER_RIGHT && scaledBorderRightWidth)
    fillPackedRGBA(
      shiftedX + scaledWidth - scaledBorderRightWidth, shiftedY + scaledBorderTopWidth,
      scaledBorderRightWidth, scaledHeight - scaledBorderBottomWidth * 2,
      borderColorDisabled);

  if (borderSides & BORDER_BOTTOM && scaledBorderBottomWidth)
    fillPackedRGBA(
      shiftedX, shiftedY + scaledHeight - scaledBorderBottomWidth,
      scaledWidth, scaledBorderBottomWidth,
      borderColorDisabled);
}

inline void UIElement::setX(int x) {
  // disambiguation
  this->x = x;

  // shiftedX is left staled
  if (globalUIContext.baseWidth)
    shiftedX = mcr_shiftX(x);
}

inline void UIElement::setY(int y) {
  // disambiguation
  this->y = y;

  // shiftedY is left staled
  if (globalUIContext.baseHeight)
    shiftedY = mcr_shiftY(y);
}

inline void UIElement::setPosition(int x, int y) {
  setX(x);
  setY(y);
}

inline void UIElement::setWidth(int width) {
  // disambiguation
  this->width = width;

  // scaledWidth is left staled
  if (globalUIContext.baseWidth)
    scaledWidth = mcr_scaleWidth(width);
}

inline void UIElement::setHeight(int height) {
  // disambiguation
  this->height = height;

  // scaledHeight is left staled
  if (globalUIContext.baseHeight)
    scaledHeight = mcr_scaleHeight(height);
}

inline void UIElement::setDimension(int width, int height) {
  setWidth(width);
  setHeight(height);
}

inline void UIElement::updateShiftedPosition() {
  if (globalUIContext.baseWidth)
    shiftedX = mcr_shiftX(x);

  if (globalUIContext.baseHeight)
    shiftedY = mcr_shiftY(y);
}

inline void UIElement::updateScaledDimension() {
  if (globalUIContext.baseWidth)
    scaledWidth = mcr_scaleWidth(width);

  if (globalUIContext.baseHeight)
    scaledHeight = mcr_scaleHeight(height);
}

inline void UIElement::updateScaledBorderWidth() {
  scaledBorderLeftWidth = mcr_scaleWidth(borderLeftWidth);
  scaledBorderRightWidth = mcr_scaleWidth(borderRightWidth);

  scaledBorderTopWidth = mcr_scaleHeight(borderTopWidth);
  scaledBorderBottomWidth = mcr_scaleHeight(borderBottomWidth);
}

void UIElement::setVisible(bool boolean) {
  visible = boolean;

  if (visible && !lastVisible) { // when element is visible and previously isn't
    lastVisible = true;

    if (onVisible)
      onVisible();
  }

  if (!visible && lastVisible) { // when element is invisible and previously isn't
    lastVisible = false;

    if (onInvisible)
      onInvisible();
  }
}

void UIElement::setEnabled(bool boolean) {
  enabled = boolean;

  if (enabled && !lastEnabled) { // when enabled and previously isn't
    lastEnabled = true;

    if (onEnable)
      onEnable();
  }

  if (!enabled && lastEnabled) { // when disabled and previously isn't
    lastEnabled = false;

    if (onDisable)
      onDisable();
  }
}

void UIElement::keyDown(int key) {
}

void UIElement::render() {
}

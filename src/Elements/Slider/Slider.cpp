
#include "Base.h"
#include "Elements/Slider/Slider.h"

#include "Presets/PresetsColor.h"

#include "ProjectUtils/TransformUtils.h"
#include "ProjectUtils/Utils.h"
#include "Utils/CursorUtils.h"
#include "Utils/ColorUtils.h"
#include "Utils/ConvertUtils.h"
#include "Utils/MathUtils.h"

// TODO: vertical slider feature

UIElementSlider::UIElementSlider() {
  UIElement::elementID = ELEMENT_SLIDER;

  UIElement::border = true;
  UIElement::borderLeftWidth = 6;
  UIElement::borderTopWidth = 6;
  UIElement::borderRightWidth = 6;
  UIElement::borderBottomWidth = 6;

  UIElementSlider::cvarValueType = CVAR_VALUE_TYPE_FLOAT;

  thumbColor = ColorUtils::packRGBAFromStruct(&presetColorWhite);
  thumbColorMouseHover = ColorUtils::packRGBAFromStruct(&presetColorOrange);
  thumbColorMouseHold = ColorUtils::packRGBAFromStruct(&presetColorOrange2);
  thumbColorDisabled = ColorUtils::packRGBAFromStruct(&presetColorGrayDisabled);

  thumbX = 0;
  thumbY = 0;
  thumbWidth = 8;
  thumbHeight = 16;
  shiftedThumbX = 0;
  shiftedThumbY = 0;
  scaledThumbWidth = 0;
  scaledThumbHeight = 0;
  minValueThumbX = 0;
  minValueThumbY = 0;
  maxValueThumbX = 0;
  maxValueThumbY = 0;

  value = 0.f;
  min = 0.f;
  max = 1.f;
  range = 1.f;
  step = 0.01f;
}

UIElementSlider::~UIElementSlider() {
}

inline void UIElementSlider::drawThumb() {
  if (!thumbColor)
    return;

  engineFunctions->pfnFillRGBA(
    shiftedThumbX, shiftedThumbY,
    scaledThumbWidth, scaledThumbHeight,
    (thumbColor >> 24) & 0xFF,
    (thumbColor >> 16) & 0xFF,
    (thumbColor >> 8) & 0xFF,
    thumbColor & 0xFF);
}

inline void UIElementSlider::drawThumbMouseHover() {
  if (!thumbColorMouseHover)
    return;

  engineFunctions->pfnFillRGBA(
    shiftedThumbX, shiftedThumbY,
    scaledThumbWidth, scaledThumbHeight,
    (thumbColorMouseHover >> 24) & 0xFF,
    (thumbColorMouseHover >> 16) & 0xFF,
    (thumbColorMouseHover >> 8) & 0xFF,
    thumbColorMouseHover & 0xFF);
}

inline void UIElementSlider::drawThumbMouseHold() {
  if (!thumbColorMouseHold)
    return;

  engineFunctions->pfnFillRGBA(
    shiftedThumbX, shiftedThumbY,
    scaledThumbWidth, scaledThumbHeight,
    (thumbColorMouseHold >> 24) & 0xFF,
    (thumbColorMouseHold >> 16) & 0xFF,
    (thumbColorMouseHold >> 8) & 0xFF,
    thumbColorMouseHold & 0xFF);
}

inline void UIElementSlider::drawThumbDisabled() {
  if (!thumbColorDisabled)
    return;

  engineFunctions->pfnFillRGBA(
    shiftedThumbX, shiftedThumbY,
    scaledThumbWidth, scaledThumbHeight,
    (thumbColorDisabled >> 24) & 0xFF,
    (thumbColorDisabled >> 16) & 0xFF,
    (thumbColorDisabled >> 8) & 0xFF,
    thumbColorDisabled & 0xFF);
}

inline void UIElementSlider::setMin(float min) {
  this->min = min;
  range = max - min;
}

inline void UIElementSlider::setMax(float max) {
  this->max = max;
  range = max - min;
}

inline void UIElementSlider::updateShiftedThumbPosition() {
  if (globalUIContext.baseWidth)
    shiftedThumbX = mcr_shiftX(thumbX);

  if (globalUIContext.baseHeight)
    shiftedThumbY = mcr_shiftY(thumbY);
}

inline void UIElementSlider::updateScaledThumbDimension() {
  if (globalUIContext.baseWidth)
    scaledThumbWidth = mcr_scaleWidth(thumbWidth);

  if (globalUIContext.baseHeight)
    scaledThumbHeight = mcr_scaleHeight(thumbHeight);
}

inline void UIElementSlider::setThumbWidth(int thumbWidth) {
  this->thumbWidth = thumbWidth;

  maxValueThumbX = x + UIElement::width - thumbWidth;
}

inline void UIElementSlider::setThumbHeight(int thumbHeight) {
  this->thumbHeight = thumbHeight;

  // TODO: vertical slider feature
}

inline void UIElementSlider::setThumbDimension(int thumbWidth, int thumbHeight) {
  setThumbWidth(thumbWidth);
  setThumbHeight(thumbHeight);
}

inline void UIElementSlider::setX(int x) {
  UIElement::setX(x);

  minValueThumbX = x;
  maxValueThumbX = x + UIElement::width - thumbWidth;
}

inline void UIElementSlider::setY(int y) {
  UIElement::setY(y);

  minValueThumbY = y;
  maxValueThumbY = y; // TODO: vertical slider feature
}

inline void UIElementSlider::setPosition(int x, int y) {
  UIElement::setPosition(x, y);

  setX(x);
  setY(y);
}

inline void UIElementSlider::setWidth(int width) {
  UIElement::setWidth(width);

  maxValueThumbX = UIElement::x + width - thumbWidth;
}

inline void UIElementSlider::setHeight(int height) {
  UIElement::setHeight(height);

  // TODO: vertical slider feature
}

inline void UIElementSlider::setDimension(int width, int height) {
  UIElement::setDimension(width, height);

  setWidth(width);
  setHeight(height);
}

void UIElementSlider::keyDown(int key) {
  if (CursorUtils::isMouseDown() || CursorUtils::isMouseHold()) {
    if (!CursorUtils::isMouseInRect(
          UIElement::shiftedX, UIElement::shiftedY,
          UIElement::scaledWidth, UIElement::scaledHeight,
          globalUIMouseContext.cursorX, globalUIMouseContext.cursorY)) {
      return;
    }

    int shiftedMinValueThumbX = mcr_shiftX(minValueThumbX);
    int shiftedMaxValueThumbX = mcr_shiftX(maxValueThumbX);

    float scale
      = static_cast<float>(
          mcr_bound(
            shiftedMinValueThumbX,
            globalUIMouseContext.cursorX - scaledThumbWidth / 2,
            shiftedMaxValueThumbX)
          - shiftedMinValueThumbX)
        / (shiftedMaxValueThumbX - shiftedMinValueThumbX);

    static float prevValue;
    value = min + mcr_round_f(((min + (max - min) * scale) - min) / step) * step;

    if (value == prevValue) // avoid redundant same value assigning
      return;

    prevValue = value;

    thumbX = mcr_bound(
      minValueThumbX,
      minValueThumbX + mcr_normalize(min, value, max) * (maxValueThumbX - minValueThumbX),
      maxValueThumbX);

    shiftedThumbX = mcr_shiftX(thumbX);

    if (cvar) {
      char buffer[16];
      ConvertUtils::fastFloatToString<1000000000, 100>(buffer, value);
      UIElementExtensionCvar::setCvarString(buffer);
    }
  }
}

inline void UIElementSlider::syncCvarValue() {
  if (UIElementExtensionCvar::cvar) {
    UIElementExtensionCvar::getCvarValue(&value);

    thumbX = mcr_bound(
      minValueThumbX,
      minValueThumbX + mcr_normalize(min, value, max) * (maxValueThumbX - minValueThumbX),
      maxValueThumbX);
  }
}

inline void UIElementSlider::setVisible(bool visible) {
  UIElement::setVisible(visible);

  if (visible && UIElementExtensionCvar::cvar)
    syncCvarValue();
}

inline void UIElementSlider::setEnabled(bool enabled) {
  UIElement::setEnabled(enabled);

  if (enabled && UIElementExtensionCvar::cvar)
    syncCvarValue();
}

inline void UIElementSlider::bindCvar(const char *cvarName) {
  UIElementExtensionCvar::bindCvar(cvarName);

  if (cvarName && UIElementExtensionCvar::cvar)
    syncCvarValue();
}

void UIElementSlider::render() {
  if (!UIElement::visible || !UIElement::width || !UIElement::height)
    return;

  if (thumbX < minValueThumbX || thumbX > maxValueThumbX)
    thumbX = mcr_bound(minValueThumbX, thumbX, maxValueThumbX);

  if (UIElement::background) {
    if (!UIElement::enabled)
      UIElement::drawBackgroundDisabled();
    else if (UIElement::mouseHover && !UIElement::mouseDown)
      UIElement::drawBackgroundMouseHover();
    else if (UIElement::mouseDown)
      UIElement::drawBackgroundMouseHold();
    else
      UIElement::drawBackground();
  }

  if (UIElement::border) {
    if (!UIElement::enabled)
      UIElement::drawBorderDisabled();
    else if (UIElement::mouseHover && !UIElement::mouseDown)
      UIElement::drawBorderMouseHover();
    else if (UIElement::mouseDown)
      UIElement::drawBorderMouseHold();
    else
      UIElement::drawBorder();
  }

  thumbY = minValueThumbY; // TODO: vertical slider feature

  updateShiftedThumbPosition();

  if (!UIElement::enabled)
    drawThumbDisabled();
  else if (UIElement::mouseHover)
    drawThumbMouseHover();
  else if (UIElement::mouseDown)
    drawThumbMouseHold();
  else
    drawThumb();
}

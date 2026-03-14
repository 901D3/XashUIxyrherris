
#include "Base.h"
#include "Elements/Text/Text.h"

#include "Utils/CharUtils.h"
#include "Utils/TransformUtils.h"
#include "Utils/MathUtils.h"
#include "Utils/Utils.h"

#include "Presets/PresetsColor.h"
#include "Primitives/Color.h"

// constructor
UIElementText::UIElementText() {
  UIElement::elementID = ELEMENT_TEXT;

  textColor = packRGBAFromStruct(&presetColorWhite);
  textColorMouseHover = packRGBAFromStruct(&presetColorWhiteMouseHover);
  textColorMouseHold = packRGBAFromStruct(&presetColorOrange2);
  textColorDisabled = packRGBAFromStruct(&presetColorGrayDisabled);

  widthScale = heightScale = 1;
  widthFitContent = heightFitContent = true;

  autoWrap = false;
  widthClip = true;
  heightClip = true;

  text = "Hello, World!";

  useConsoleFont = false; // fallback to DrawConsoleString
}

UIElementText::~UIElementText() {
}

void UIElementText::render() {
  if (!UIElement::visible || (!UIElement::width && !widthFitContent) || (!UIElement::height && !heightFitContent))
    return;

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

  int drawX = UIElement::shiftedX;
  int drawY = UIElement::shiftedY;

  int maxHeight = 0;

  for (int i = 0; i < text.length();) {
    unsigned int character = CharUtils::UTF8ToUnicodeCP(text, i); // increment i too
    CharUtils::unicodeCPToCP1251(character);

    BitmapGlyph *characterGlyph = &bitmapFontContext.glyphs[character];

    // apply UI scaling too
    int scaledCharacterGlyphWidth = mcr_scaleWidth(mcr_floor_positive(characterGlyph->width * widthScale));
    int scaledCharacterGlyphHeight = mcr_scaleHeight(mcr_floor_positive(characterGlyph->height * heightScale));

    if (character == ' ') { // early continue if the current char is a space
      drawX += scaledCharacterGlyphWidth;
      continue;
    }

    if (maxHeight < scaledCharacterGlyphHeight)
      maxHeight = scaledCharacterGlyphHeight;

    wrect_t glyphRectangle;
    glyphRectangle.left = characterGlyph->atlasX;
    glyphRectangle.top = characterGlyph->atlasY;

    glyphRectangle.right = characterGlyph->atlasX + characterGlyph->width;
    glyphRectangle.bottom = characterGlyph->atlasY + characterGlyph->height;

    // TODO: add auto wrap
    // if (autoWrap);

    // color is reset every PIC_Draw so we keep changing color
    if (!UIElement::enabled)
      engineFunctions->pfnPIC_Set(
        bitmapFontContext.fontHImage,
        textColorDisabled & 0xFF,
        (textColorDisabled >> 8) & 0xFF,
        (textColorDisabled >> 16) & 0xFF,
        (textColorDisabled >> 24) & 0xFF);
    else if (UIElement::mouseHover && !UIElement::mouseDown)
      engineFunctions->pfnPIC_Set(
        bitmapFontContext.fontHImage,
        textColorMouseHover & 0xFF,
        (textColorMouseHover >> 8) & 0xFF,
        (textColorMouseHover >> 16) & 0xFF,
        (textColorMouseHover >> 24) & 0xFF);
    else if (UIElement::mouseDown)
      engineFunctions->pfnPIC_Set(
        bitmapFontContext.fontHImage,
        textColorMouseHold & 0xFF,
        (textColorMouseHold >> 8) & 0xFF,
        (textColorMouseHold >> 16) & 0xFF,
        (textColorMouseHold >> 24) & 0xFF);
    else
      engineFunctions->pfnPIC_Set(
        bitmapFontContext.fontHImage,
        textColor & 0xFF,
        (textColor >> 8) & 0xFF,
        (textColor >> 16) & 0xFF,
        (textColor >> 24) & 0xFF);

    if (useConsoleFont) {
      char string[2] = {static_cast<char>(character), 0};

      engineFunctions->pfnDrawConsoleString(drawX, drawY, string);
    } else {
      if (additiveBlend)
        engineFunctions->pfnPIC_DrawAdditive(
          drawX,
          drawY,
          scaledCharacterGlyphWidth,
          scaledCharacterGlyphHeight,
          &glyphRectangle);
      else
        engineFunctions->pfnPIC_DrawTrans(
          drawX,
          drawY,
          scaledCharacterGlyphWidth,
          scaledCharacterGlyphHeight,
          &glyphRectangle);
    }

    drawX += scaledCharacterGlyphWidth;
    // drawY += scaledCharacterGlyphHeight;
  }

  int maxWidth = drawX - UIElement::shiftedX;

  if (widthFitContent) {
    int baseFitWidth = mcr_unscaleWidth(maxWidth);

    if (baseFitWidth != UIElement::width)
      UIElement::setWidth(baseFitWidth);
  }

  if (heightFitContent) {
    int baseFitHeight = mcr_unscaleHeight(maxHeight);

    if (baseFitHeight != UIElement::height)
      UIElement::setHeight(baseFitHeight);
  }
}

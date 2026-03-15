
#pragma once

#include "Base.h"
#include "Elements/ElementExtensions/ElementExtensionCvar.h"

class UIElementSlider
    : public UIElement,
      public UIElementExtensionCvar
{

public:
  unsigned int thumbColor;
  unsigned int thumbColorMouseHover;
  unsigned int thumbColorMouseHold;
  unsigned int thumbColorDisabled;

  int thumbX;
  int thumbY;

  int thumbWidth;
  int thumbHeight;

  int shiftedThumbX;
  int shiftedThumbY;

  int scaledThumbWidth;
  int scaledThumbHeight;

  int minValueThumbX;
  int minValueThumbY;

  int maxValueThumbX;
  int maxValueThumbY;

  bool thumbMaxContent; // css

  float value;
  float min;
  float max;
  float range; // cache
  float step;

  bool isDragging;

  UIElementSlider();
  virtual ~UIElementSlider();

  virtual void drawThumb();
  virtual void drawThumbMouseHover();
  virtual void drawThumbMouseHold();
  virtual void drawThumbDisabled();

  virtual void setMin(float min);
  virtual void setMax(float max);

  virtual void updateShiftedThumbPosition();
  virtual void updateScaledThumbDimension();

  virtual void setThumbWidth(int thumbWidth);
  virtual void setThumbHeight(int thumbHeight);
  virtual void setThumbDimension(int thumbWidth, int thumbHeight);

  virtual void syncCvarValue();

  // overrides
  void setX(int x);
  void setY(int y);
  void setPosition(int x, int y);

  void setWidth(int width);
  void setHeight(int height);
  void setDimension(int width, int height);

  void setVisible(bool visible);
  void setEnabled(bool enabled);

  void bindCvar(const char *cvarName);

  void keyDown(int key);

  void render(); // modify UIElement's render()
};

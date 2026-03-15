
#pragma once

#include "Elements/ElementBase.h" // UIElement

#define MAX_ELEMENTS 128

class UIMenu {
public:
  bool initialized;

  UIElement *elementsContainer[MAX_ELEMENTS]; // ptr to elements
  int elementCount;

  // TODO: an array of hovering, pressing, focusing elements for multitouch
  // Src/Base.cpp/elementMouseController
  UIElement *hoveringElement; // mouse only?
  UIElement *pressingElement;
  UIElement *focusingElement; // currently unused

  UIMenu();
  virtual ~UIMenu();

  // add an UIElement to elementsContainer
  virtual void pushBackElement(UIElement *element);

  // remove an UIElement from elementsContainer with a specified id
  virtual void removeElement(const char *id);

  // get an UIElement from elementsContainer with a specified id
  virtual void *getElement(const char *id); // remember to cast to UIElement

  // go through every elements and call keyDown
  virtual void keyDownMenu(int key);

  // go through every elements and call render
  virtual void renderMenu();
};

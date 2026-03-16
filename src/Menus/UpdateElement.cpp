
#include "Base.h"
#include "Commands.h"
#include "Elements/Slider/Slider.h"

#include "Utils/CursorUtils.h"

void elementCvarSync() {
  UIMenu *currentMenu = CURRENT_MENU;

  // go through all element in currentMenu
  for (int i = 0; i < currentMenu->UIMenu::elementCount; i++) {
    UIElement *currentElement = currentMenu->elementsContainer[i]; // get the current element

    if (!currentElement)
      continue;

    if (currentElement->UIElement::elementID == ELEMENT_SLIDER)
      (static_cast<UIElementSlider *>(currentElement))->UIElementSlider::syncCvarValue();
  }
}

// update shifts and scale for every elements
void elementsShiftsAndScaleUpdate() {
  UIMenu *currentMenu = CURRENT_MENU;

  // go through all element in currentMenu
  for (int i = 0; i < currentMenu->UIMenu::elementCount; i++) {
    UIElement *currentElement = currentMenu->elementsContainer[i]; // get the current element

    if (!currentElement)
      continue;

    currentElement->UIElement::updateShiftedPosition();
    currentElement->UIElement::updateScaledDimension();

    if (currentElement->UIElement::border)
      currentElement->UIElement::updateScaledBorderWidth();

    if (currentElement->UIElement::elementID == ELEMENT_SLIDER) {
      UIElementSlider *slider = static_cast<UIElementSlider *>(currentElement);

      slider->UIElementSlider::updateShiftedThumbPosition();
      slider->UIElementSlider::updateScaledThumbDimension();
    }
  }
}

// controls the hover and mouse LMB down/hold/up state
void elementMouseEventsController() {
  UIMenu *currentMenu = CURRENT_MENU;
  UIElement *newHoveringElement = nullptr;

  // go through all element in currentMenu
  for (int i = currentMenu->UIMenu::elementCount - 1; i >= 0; i--) {
    UIElement *currentElement = currentMenu->elementsContainer[i]; // get the current element

    if (!currentElement->UIElement::enabled)
      continue;

    if (CursorUtils::isMouseInRect(
          currentElement->UIElement::shiftedX,
          currentElement->UIElement::shiftedY,
          currentElement->UIElement::scaledWidth,
          currentElement->UIElement::scaledHeight,
          globalUIMouseContext.cursorX,
          globalUIMouseContext.cursorY)) { // when mouse is hovering on the element
      newHoveringElement = currentElement; // save the hovering element
      break;
    }
  }

  UIElement *oldHoveringElement = currentMenu->hoveringElement;

  if (oldHoveringElement != newHoveringElement) { // compare ptrs

    if (newHoveringElement) { // IMPORTANT: there is a case where the mouse is not hovered on any element so we check the ptr
      newHoveringElement->UIElement::mouseHover = true;

      // when mouse is hovered in and previously isn't
      if (!newHoveringElement->UIElement::lastMouseHover) {
        newHoveringElement->UIElement::lastMouseHover = true;

        newHoveringElement->UIElement::onMouseHoverIn();
      }
    }

    // when mouse is hovered out
    if (oldHoveringElement && oldHoveringElement->UIElement::mouseHover) {
      oldHoveringElement->mouseHover = false;

      if (oldHoveringElement->UIElement::lastMouseHover) {
        oldHoveringElement->UIElement::lastMouseHover = false;

        oldHoveringElement->UIElement::onMouseHoverOut();
      }
    }

    // when mouse is hovered out and previously is
    // do nothing
  }

  // when mouse is hovered in and previously is
  if (newHoveringElement && newHoveringElement->UIElement::lastMouseHover)
    newHoveringElement->UIElement::onMouseHover();

  currentMenu->UIMenu::hoveringElement = newHoveringElement; // update old hovering element to the new one

  if (CursorUtils::isMouseDown(globalUIMouseContext.mouseDown, globalUIMouseContext.lastMouseDown) && newHoveringElement) {
    currentMenu->UIMenu::pressingElement = newHoveringElement;

    newHoveringElement->UIElement::mouseDown = true;

    if (!newHoveringElement->UIElement::lastMouseDown) {
      newHoveringElement->UIElement::lastMouseDown = true;

      newHoveringElement->UIElement::onMouseDown();
    }
  }

  UIElement *pressingElement = currentMenu->UIMenu::pressingElement;

  if (pressingElement) {
    if (CursorUtils::isMouseHold(globalUIMouseContext.mouseDown, globalUIMouseContext.lastMouseDown))
      pressingElement->UIElement::onMouseHold(); // call onMouseHold continuously

    if (CursorUtils::isMouseUp(globalUIMouseContext.mouseDown, globalUIMouseContext.lastMouseDown)) {
      pressingElement->UIElement::mouseDown = false;

      if (pressingElement->UIElement::lastMouseDown) {
        pressingElement->UIElement::lastMouseDown = false;

        if (pressingElement == currentMenu->hoveringElement) // if the pressing element is also the hovering element && check ptr to function
          pressingElement->UIElement::onMouseUp();
      }
    }

    // there are some cases where element mouse hold is stale
    if (CursorUtils::isMouseIdle(globalUIMouseContext.mouseDown, globalUIMouseContext.lastMouseDown)) {
      pressingElement->UIElement::mouseDown = false;
      pressingElement->UIElement::lastMouseDown = false;
    }
  }
}

void elementMouseEventsReset() {
  UIMenu *currentMenu = CURRENT_MENU;

  // go through all element in currentMenu
  for (int i = 0; i < currentMenu->UIMenu::elementCount; i++) {
    UIElement *currentElement = currentMenu->elementsContainer[i]; // get the current element

    if (!currentElement)
      continue;

    currentElement->UIElement::mouseHover = false;
    currentElement->UIElement::lastMouseHover = false;

    currentElement->UIElement::mouseDown = false;
    currentElement->UIElement::lastMouseDown = false;
  }
}

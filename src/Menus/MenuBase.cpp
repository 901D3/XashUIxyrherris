
#include "Menus/MenuBase.h" // UIMenu
#include "Utils/Utils.h"    // mcr_ConsoleDebugLog

UIMenu::UIMenu() {
  elementCount = 0;

  hoveringElement = nullptr;
  pressingElement = nullptr;
  focusingElement = nullptr;
}

UIMenu::~UIMenu() {
  // TODO: add cleanup scripts
}

void UIMenu::pushBackElement(UIElement *element) {
  if (elementCount >= MAX_ELEMENTS) {
    mcr_ConsoleDebugLog("Elements stack is full: %i", MAX_ELEMENTS);
    return;
  }

  if (!element) {
    mcr_ConsoleDebugLog("Invalid element: %i", element);
    return;
  }

  // check if the new element's id matches any other element's id
  for (int i = 0; i < elementCount; i++) {
    if (elementsContainer[i]->identifier == element->identifier) {
      mcr_ConsoleDebugLog("An element with identifier \"%s\" already exists", element->identifier.c_str());
      return;
    }
  }

  elementsContainer[elementCount++] = element;
}

void UIMenu::removeElement(const char *id) {
  if (elementCount <= 0) {
    mcr_ConsoleDebugLog("No element to remove");
    return;
  }

  for (int i = 0; i < elementCount; i++) {
    if (strcmp(elementsContainer[i]->identifier.c_str(), id) == 0) {
      for (int j = i; j < elementCount - 1; j++) {
        elementsContainer[j] = elementsContainer[j + 1];
      }

      elementsContainer[--elementCount] = nullptr;
      return;
    }
  }

  mcr_ConsoleDebugLog("Element id \"%s\" not found", id);
}

void *UIMenu::getElement(const char *id) { // void* because there is a path where the function returns nullptr
  for (int i = 0; i < elementCount; i++) {
    if (strcmp(elementsContainer[i]->identifier.c_str(), id) == 0)
      return elementsContainer[i];
  }

  mcr_ConsoleDebugLog("Element id \"%s\" not found", id);
  return nullptr;
}

void UIMenu::keyDownMenu(int key) {
  for (int i = 0; i < elementCount; i++)
    elementsContainer[i]->keyDown(key);
}

void UIMenu::renderMenu() {
  for (int i = 0; i < elementCount; i++)
    elementsContainer[i]->render();
}

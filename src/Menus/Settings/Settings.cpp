
#include "Menus/MenusExport.h"
#include "Elements/Text/Text.h"

#include "Presets/PresetsTransform.h"

#include "ProjectUtils/Utils.h"

#define MENU_SETTINGS_ELEMENT_COUNT 7

UIMenu menuSettings;

static void controlsMenu() {
  navigateToMenu(MENU_SETTINGS_CONTROLS);
}

static void audioMenu() {
  navigateToMenu(MENU_SETTINGS_AUDIO);
}

static void videoMenu() {
}

static void touchMenu() {
}

static void joystickMenu() {
}

static void updateMenu() {
}

void menuSettingsRenderWrapper() {
  menuSettings.UIMenu::renderMenu();
}

void menuSettingsInit() {
  if (!menuSettings.UIMenu::initialized)
    menuSettings.UIMenu::initialized = true;
  else
    return;

  Position positions[MENU_SETTINGS_ELEMENT_COUNT];
  buttonAlignmentGenerateList(positions, UI_ITEMMARGINX, UI_ITEMMARGINY, 0, UI_ITEMMARGINY, MENU_SETTINGS_ELEMENT_COUNT);

  static UIElementText controlsButton;
  controlsButton.UIElement::identifier = "controlsButton";
  controlsButton.UIElementText::widthScale = 1;
  controlsButton.UIElementText::heightScale = 1.3;
  controlsButton.UIElementText::widthFitContent = true;
  controlsButton.UIElementText::heightFitContent = true;

  static UIElementText audioButton;
  audioButton.UIElement::identifier = "audioButton";
  audioButton.UIElementText::widthScale = 1;
  audioButton.UIElementText::heightScale = 1.3;
  audioButton.UIElementText::widthFitContent = true;
  audioButton.UIElementText::heightFitContent = true;

  static UIElementText videoButton;
  videoButton.UIElement::identifier = "videoButton";
  videoButton.UIElementText::widthScale = 1;
  videoButton.UIElementText::heightScale = 1.3;
  videoButton.UIElementText::widthFitContent = true;
  videoButton.UIElementText::heightFitContent = true;

  static UIElementText touchButton;
  touchButton.UIElement::identifier = "touchButton";
  touchButton.UIElementText::widthScale = 1;
  touchButton.UIElementText::heightScale = 1.3;
  touchButton.UIElementText::widthFitContent = true;
  touchButton.UIElementText::heightFitContent = true;

  static UIElementText joystickButton;
  joystickButton.UIElement::identifier = "joystickButton";
  joystickButton.UIElementText::widthScale = 1;
  joystickButton.UIElementText::heightScale = 1.3;
  joystickButton.UIElementText::widthFitContent = true;
  joystickButton.UIElementText::heightFitContent = true;

  static UIElementText updateButton;
  updateButton.UIElement::identifier = "updateButton";
  updateButton.UIElementText::widthScale = 1;
  updateButton.UIElementText::heightScale = 1.3;
  updateButton.UIElementText::widthFitContent = true;
  updateButton.UIElementText::heightFitContent = true;

  static UIElementText doneButton;
  doneButton.UIElement::identifier = "doneButton";
  doneButton.UIElementText::widthScale = 1;
  doneButton.UIElementText::heightScale = 1.3;
  doneButton.UIElementText::widthFitContent = true;
  doneButton.UIElementText::heightFitContent = true;

  controlsButton.UIElementText::text = "Controls";
  controlsButton.UIElement::setPosition(positions[0].x, positions[0].y);
  controlsButton.UIElement::onMouseUp = &controlsMenu;
  menuSettings.UIMenu::pushBackElement(&controlsButton);

  audioButton.UIElementText::text = "Audio";
  audioButton.UIElement::setPosition(positions[1].x, positions[1].y);
  audioButton.UIElement::onMouseUp = &audioMenu;
  menuSettings.UIMenu::pushBackElement(&audioButton);

  videoButton.UIElementText::text = "Video";
  videoButton.UIElement::setPosition(positions[2].x, positions[2].y);
  videoButton.UIElement::onMouseUp = &videoMenu;
  menuSettings.UIMenu::pushBackElement(&videoButton);

  touchButton.UIElementText::text = "Touch";
  touchButton.UIElement::setPosition(positions[3].x, positions[3].y);
  touchButton.UIElement::onMouseUp = &touchMenu;
  menuSettings.UIMenu::pushBackElement(&touchButton);

  joystickButton.UIElementText::text = "Joystick";
  joystickButton.UIElement::setPosition(positions[4].x, positions[4].y);
  joystickButton.UIElement::onMouseUp = &joystickMenu;
  menuSettings.UIMenu::pushBackElement(&joystickButton);

  updateButton.UIElementText::text = "Update";
  updateButton.UIElement::setPosition(positions[5].x, positions[5].y);
  updateButton.UIElement::onMouseUp = &updateMenu;
  menuSettings.UIMenu::pushBackElement(&updateButton);

  doneButton.UIElementText::text = "Done";
  doneButton.UIElement::setPosition(positions[6].x, positions[6].y);
  doneButton.UIElement::onMouseUp = &goBackToLastMenu;
  menuSettings.UIMenu::pushBackElement(&doneButton);
}

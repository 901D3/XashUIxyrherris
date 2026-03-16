
#include "XashEngineRelated/XashKey.h"

#include "Menus/MenusExport.h"
#include "Elements/Text/Text.h"

#include "Presets/PresetsTransform.h"

#include "ProjectUtils/Utils.h"

#define MENU_SETTINGS_CONTROLS_ELEMENT_COUNT 4

UIMenu menuSettingsControls;

static void useDefault() {
}

static void advancedControlsMenu() {
}

static void ok() {
}

static void cancel() {
}

void menuSettingsControlsRenderWrapper() {
  menuSettingsControls.UIMenu::renderMenu();
}

void menuSettingsControlsInit() {
  if (!menuSettingsControls.UIMenu::initialized)
    menuSettingsControls.UIMenu::initialized = true;
  else
    return;

  Position positions[MENU_SETTINGS_CONTROLS_ELEMENT_COUNT];
  buttonAlignmentGenerateList(positions, UI_ITEMMARGINX, UI_ITEMMARGINY, 0, UI_ITEMMARGINY, MENU_SETTINGS_CONTROLS_ELEMENT_COUNT);

  static UIElementText useDefaultsButton;
  useDefaultsButton.UIElement::identifier = "useDefaultsButton";
  useDefaultsButton.UIElementText::widthScale = 1;
  useDefaultsButton.UIElementText::heightScale = 1.3;
  useDefaultsButton.UIElementText::widthFitContent = true;
  useDefaultsButton.UIElementText::heightFitContent = true;

  static UIElementText advancedControlsButton;
  advancedControlsButton.UIElement::identifier = "advancedControlsButton";
  advancedControlsButton.UIElementText::widthScale = 1;
  advancedControlsButton.UIElementText::heightScale = 1.3;
  advancedControlsButton.UIElementText::widthFitContent = true;
  advancedControlsButton.UIElementText::heightFitContent = true;

  static UIElementText okButton;
  okButton.UIElement::identifier = "okButton";
  okButton.UIElementText::widthScale = 1;
  okButton.UIElementText::heightScale = 1.3;
  okButton.UIElementText::widthFitContent = true;
  okButton.UIElementText::heightFitContent = true;

  static UIElementText cancelButton;
  cancelButton.UIElement::identifier = "cancelButton";
  cancelButton.UIElementText::widthScale = 1;
  cancelButton.UIElementText::heightScale = 1.3;
  cancelButton.UIElementText::widthFitContent = true;
  cancelButton.UIElementText::heightFitContent = true;

  useDefaultsButton.UIElementText::text = "Use Defaults";
  useDefaultsButton.UIElement::setPosition(positions[0].x, positions[0].y);
  useDefaultsButton.UIElement::onMouseUp = &useDefault;
  menuSettingsControls.UIMenu::pushBackElement(&useDefaultsButton);

  advancedControlsButton.UIElementText::text = "Adv. Controls";
  advancedControlsButton.UIElement::setPosition(positions[1].x, positions[1].y);
  advancedControlsButton.UIElement::onMouseUp = &advancedControlsMenu;
  menuSettingsControls.UIMenu::pushBackElement(&advancedControlsButton);

  okButton.UIElementText::text = "Ok";
  okButton.UIElement::setPosition(positions[2].x, positions[2].y);
  okButton.UIElement::onMouseUp = &ok;
  menuSettingsControls.UIMenu::pushBackElement(&okButton);

  cancelButton.UIElementText::text = "Cancel";
  cancelButton.UIElement::setPosition(positions[3].x, positions[3].y);
  cancelButton.UIElement::onMouseUp = &cancel;
  menuSettingsControls.UIMenu::pushBackElement(&cancelButton);
}

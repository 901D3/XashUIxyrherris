
#include "Cvars/Cvars.h"
#include "Menus/MenusExport.h"

#include "Elements/Text/Text.h"
#include "Elements/Slider/Slider.h"
#include "Elements/ToggleButton/ToggleButton.h"

#include "Primitives/Key.h"

#include "Presets/PresetsTransform.h"

#include "Utils/Utils.h"

#define MENU_SETTINGS_AUDIO_ELEMENT_COUNT 20

UIMenu menuSettingsAudio;

static void useDefault() {
}

static void noDSP() {
  (static_cast<UIElementToggleButton *>(menuSettingsAudio.UIMenu::getElement("noDSPToggleButton")))->UIElementToggleButton::toggleHelper();
}

void menuSettingsAudioRenderWrapper() {
  menuSettingsAudio.UIMenu::renderMenu();
}

void menuSettingsAudioInit() {
  if (!menuSettingsAudio.UIMenu::initialized)
    menuSettingsAudio.UIMenu::initialized = true;
  else
    return;

  Position positions[MENU_SETTINGS_AUDIO_ELEMENT_COUNT];
  buttonAlignmentGenerateList(positions, UI_ITEMMARGINX, UI_ITEMMARGINY, 0, UI_ITEMMARGINY, MENU_SETTINGS_AUDIO_ELEMENT_COUNT);

  static UIElementText doneButton;
  doneButton.UIElement::identifier = "doneButton";
  doneButton.UIElementText::widthScale = 1;
  doneButton.UIElementText::heightScale = 1.3;
  doneButton.UIElementText::widthFitContent = true;
  doneButton.UIElementText::heightFitContent = true;

  static UIElementText volumeText;
  volumeText.UIElement::identifier = "volumeText";
  volumeText.UIElementText::widthScale = 1;
  volumeText.UIElementText::heightScale = 1.3;
  volumeText.UIElementText::widthFitContent = true;
  volumeText.UIElementText::heightFitContent = true;

  static UIElementText mp3VolumeText;
  mp3VolumeText.UIElement::identifier = "mp3VolumeText";
  mp3VolumeText.UIElementText::widthScale = 1;
  mp3VolumeText.UIElementText::heightScale = 1.3;
  mp3VolumeText.UIElementText::widthFitContent = true;
  mp3VolumeText.UIElementText::heightFitContent = true;

  static UIElementText suitVolumeText;
  suitVolumeText.UIElement::identifier = "suitVolumeText";
  suitVolumeText.UIElementText::widthScale = 1;
  suitVolumeText.UIElementText::heightScale = 1.3;
  suitVolumeText.UIElementText::widthFitContent = true;
  suitVolumeText.UIElementText::heightFitContent = true;

  static UIElementSlider volumeSlider;
  volumeSlider.UIElement::identifier = "volumeSlider";
  volumeSlider.UIElementSlider::setWidth(300);
  volumeSlider.UIElementSlider::setHeight(16);

  static UIElementSlider mp3Volume;
  mp3Volume.UIElement::identifier = "mp3Volume";
  mp3Volume.UIElementSlider::setWidth(300);
  mp3Volume.UIElementSlider::setHeight(16);

  static UIElementSlider suitVolume;
  suitVolume.UIElement::identifier = "suitVolume";
  suitVolume.UIElementSlider::setWidth(300);
  suitVolume.UIElementSlider::setHeight(16);

  static UIElementToggleButton noDSPToggleButton;
  noDSPToggleButton.UIElement::identifier = "noDSPToggleButton";

  doneButton.UIElementText::text = "Done";
  doneButton.UIElement::setPosition(positions[0].x, positions[0].y);
  doneButton.UIElement::onMouseUp = &goBackToLastMenu;
  menuSettingsAudio.UIMenu::pushBackElement(&doneButton);

  volumeText.UIElementText::text = "Game Sound Volume";
  volumeText.UIElement::setPosition(positions[2].x, positions[2].y);
  menuSettingsAudio.UIMenu::pushBackElement(&volumeText);

  volumeSlider.UIElementSlider::bindCvar("volume");
  volumeSlider.UIElement::setPosition(positions[3].x, positions[3].y);
  menuSettingsAudio.UIMenu::pushBackElement(&volumeSlider);

  mp3VolumeText.UIElementText::text = "Game Music Volume";
  mp3VolumeText.UIElement::setPosition(positions[5].x, positions[5].y);
  menuSettingsAudio.UIMenu::pushBackElement(&mp3VolumeText);

  mp3Volume.UIElementSlider::bindCvar("MP3Volume");
  mp3Volume.UIElement::setPosition(positions[6].x, positions[6].y);
  menuSettingsAudio.UIMenu::pushBackElement(&mp3Volume);

  suitVolumeText.UIElementText::text = "Suit Volume";
  suitVolumeText.UIElement::setPosition(positions[8].x, positions[8].y);
  menuSettingsAudio.UIMenu::pushBackElement(&suitVolumeText);

  suitVolume.UIElementSlider::bindCvar("suitvolume");
  suitVolume.UIElement::setPosition(positions[9].x, positions[9].y);
  menuSettingsAudio.UIMenu::pushBackElement(&suitVolume);

  noDSPToggleButton.UIElementExtensionCvar::bindCvar("room_off");
  noDSPToggleButton.UIElement::onMouseUp = &noDSP;
  noDSPToggleButton.UIElement::setPosition(positions[10].x, positions[10].y);
  menuSettingsAudio.UIMenu::pushBackElement(&noDSPToggleButton);
}

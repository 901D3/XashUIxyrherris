
#include "XashEngineRelated/XashKey.h"

#include "Menus/MenusExport.h"
#include "Elements/Text/Text.h"

#include "Presets/PresetsTransform.h"

#include "ProjectUtils/Utils.h"

#define MENU_MAIN_ELEMENT_COUNT 10

UIMenu menuMain;

static void openConsole() {
  setKeyDestWrapper(KEY_CONSOLE);
}

static void resumeGame() {
  setKeyDestWrapper(KEY_GAME);
  globalUIContext.processNextFrame = false;
}

static void disconnect() {
  engineFunctions->pfnClientCmd(false, "disconnect\n");
  setKeyDestWrapper(KEY_MENU);

  (static_cast<UIElement *>(menuMain.UIMenu::getElement("resumeGameButton")))->UIElement::setEnabled(false);
  (static_cast<UIElement *>(menuMain.UIMenu::getElement("disconnectButton")))->UIElement::setEnabled(false);
}

static void newGameMenu() {
}

static void hazardCourse() {
  engineFunctions->pfnClientCmd(false, "hazardcourse\n");
  setKeyDestWrapper(KEY_GAME);

  (static_cast<UIElement *>(menuMain.UIMenu::getElement("resumeGameButton")))->UIElement::setEnabled(true);
  (static_cast<UIElement *>(menuMain.UIMenu::getElement("disconnectButton")))->UIElement::setEnabled(true);
}

static void multiPlayerMenu() {
}

static void settingsMenu() {
  navigateToMenu(MENU_SETTINGS);
}

static void changeGameMenu() {
}

static void previews() {
  engineFunctions->pfnShellExecute("http://store.steampowered.com/app/70/", NULL, false);
}

static void quitGame() {
  engineFunctions->pfnClientCmd(false, "quit\n");
}

void menuMainRenderWrapper() {
  menuMain.UIMenu::renderMenu();
}

void menuMainInit() {
  if (!menuMain.UIMenu::initialized)
    menuMain.UIMenu::initialized = true;
  else
    return;

  Position positions[MENU_MAIN_ELEMENT_COUNT];
  buttonAlignmentGenerateList(positions, UI_ITEMMARGINX, UI_ITEMMARGINY, 0, UI_ITEMMARGINY, MENU_MAIN_ELEMENT_COUNT);

  static UIElementText consoleButton;
  consoleButton.UIElement::identifier = "consoleButton";
  consoleButton.UIElementText::widthScale = 1;
  consoleButton.UIElementText::heightScale = 1.3;
  consoleButton.UIElementText::widthFitContent = true;
  consoleButton.UIElementText::heightFitContent = true;
  consoleButton.UIElementText::background = true;
  consoleButton.UIElementText::border = true;

  static UIElementText resumeGameButton;
  resumeGameButton.UIElement::identifier = "resumeGameButton";
  resumeGameButton.UIElementText::widthScale = 1;
  resumeGameButton.UIElementText::heightScale = 1.3;
  resumeGameButton.UIElementText::widthFitContent = true;
  resumeGameButton.UIElementText::heightFitContent = true;

  static UIElementText disconnectButton;
  disconnectButton.UIElement::identifier = "disconnectButton";
  disconnectButton.UIElementText::widthScale = 1;
  disconnectButton.UIElementText::heightScale = 1.3;
  disconnectButton.UIElementText::widthFitContent = true;
  disconnectButton.UIElementText::heightFitContent = true;

  static UIElementText newGameButton;
  newGameButton.UIElement::identifier = "newGameButton";
  newGameButton.UIElementText::widthScale = 1;
  newGameButton.UIElementText::heightScale = 1.3;
  newGameButton.UIElementText::widthFitContent = true;
  newGameButton.UIElementText::heightFitContent = true;

  static UIElementText trainingRoomButton;
  trainingRoomButton.UIElement::identifier = "trainingRoomButton";
  trainingRoomButton.UIElementText::widthScale = 1;
  trainingRoomButton.UIElementText::heightScale = 1.3;
  trainingRoomButton.UIElementText::widthFitContent = true;
  trainingRoomButton.UIElementText::heightFitContent = true;

  static UIElementText multiPlayerButton;
  multiPlayerButton.UIElement::identifier = "multiPlayerButton";
  multiPlayerButton.UIElementText::widthScale = 1;
  multiPlayerButton.UIElementText::heightScale = 1.3;
  multiPlayerButton.UIElementText::widthFitContent = true;
  multiPlayerButton.UIElementText::heightFitContent = true;

  static UIElementText settingsButton;
  settingsButton.UIElement::identifier = "settingsButton";
  settingsButton.UIElementText::widthScale = 1;
  settingsButton.UIElementText::heightScale = 1.3;
  settingsButton.UIElementText::widthFitContent = true;
  settingsButton.UIElementText::heightFitContent = true;

  static UIElementText changeGameButton;
  changeGameButton.UIElement::identifier = "changeGameButton";
  changeGameButton.UIElementText::widthScale = 1;
  changeGameButton.UIElementText::heightScale = 1.3;
  changeGameButton.UIElementText::widthFitContent = true;
  changeGameButton.UIElementText::heightFitContent = true;

  static UIElementText previewsButton;
  previewsButton.UIElement::identifier = "previewsButton";
  previewsButton.UIElementText::widthScale = 1;
  previewsButton.UIElementText::heightScale = 1.3;
  previewsButton.UIElementText::widthFitContent = true;
  previewsButton.UIElementText::heightFitContent = true;

  static UIElementText quitGameButton;
  quitGameButton.UIElement::identifier = "quitGameButton";
  quitGameButton.UIElementText::widthScale = 1;
  quitGameButton.UIElementText::heightScale = 1.3;
  quitGameButton.UIElementText::widthFitContent = true;
  quitGameButton.UIElementText::heightFitContent = true;

  consoleButton.UIElementText::text = "Console";
  consoleButton.UIElement::setPosition(positions[0].x, positions[0].y);
  consoleButton.UIElement::onMouseUp = &openConsole;
  menuMain.UIMenu::pushBackElement(&consoleButton);

  resumeGameButton.UIElementText::text = "Resume";
  resumeGameButton.UIElement::setEnabled(false);
  resumeGameButton.UIElement::setPosition(positions[1].x, positions[1].y);
  resumeGameButton.UIElement::onMouseUp = &resumeGame;
  menuMain.UIMenu::pushBackElement(&resumeGameButton);

  disconnectButton.UIElementText::text = "Disconnect";
  disconnectButton.UIElement::setEnabled(false);
  disconnectButton.UIElement::setPosition(positions[2].x, positions[2].y);
  disconnectButton.UIElement::onMouseUp = &disconnect;
  menuMain.UIMenu::pushBackElement(&disconnectButton);

  newGameButton.UIElementText::text = "New Game";
  newGameButton.UIElement::setPosition(positions[3].x, positions[3].y);
  newGameButton.UIElement::onMouseUp = &newGameMenu;
  menuMain.UIMenu::pushBackElement(&newGameButton);

  trainingRoomButton.UIElementText::text = "Hazard Course";
  trainingRoomButton.UIElement::setPosition(positions[4].x, positions[4].y);
  trainingRoomButton.UIElement::onMouseUp = &hazardCourse;
  menuMain.UIMenu::pushBackElement(&trainingRoomButton);

  multiPlayerButton.UIElementText::text = "Multiplayer";
  multiPlayerButton.UIElement::setPosition(positions[5].x, positions[5].y);
  multiPlayerButton.UIElement::onMouseUp = &multiPlayerMenu;
  menuMain.UIMenu::pushBackElement(&multiPlayerButton);

  settingsButton.UIElementText::text = "Configuration";
  settingsButton.UIElement::setPosition(positions[6].x, positions[6].y);
  settingsButton.UIElement::onMouseUp = &settingsMenu;
  menuMain.UIMenu::pushBackElement(&settingsButton);

  changeGameButton.UIElementText::text = "Change Game";
  changeGameButton.UIElement::setPosition(positions[7].x, positions[7].y);
  changeGameButton.UIElement::onMouseUp = &changeGameMenu;
  menuMain.UIMenu::pushBackElement(&changeGameButton);

  previewsButton.UIElementText::text = "Previews";
  previewsButton.UIElement::setPosition(positions[8].x, positions[8].y);
  previewsButton.UIElement::onMouseUp = &previews;
  menuMain.UIMenu::pushBackElement(&previewsButton);

  quitGameButton.UIElementText::text = "Quit Game";
  quitGameButton.UIElement::setPosition(positions[9].x, positions[9].y);
  quitGameButton.UIElement::onMouseUp = &quitGame;
  menuMain.UIMenu::pushBackElement(&quitGameButton);
}

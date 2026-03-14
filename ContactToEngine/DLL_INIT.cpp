
#include "Base.h"
#include "extdll_menu.h"
#include "EngineStuff.h"

#include "Utils/Utils.h"

#include "FUNCTION_EXPORTING.h"

ui_enginefuncs_t *engineFunctions;
ui_extendedfuncs_t *extendedFunctions;
gameinfo2_t *globalGameInfo;
ui_globalvars_t *globalVars;

static UI_FUNCTIONS exportedUIFunctions = {
  &_baseVideoInit,     // UI_VidInit
  &_baseInit,          // UI_Init
  &UI_Shutdown,        // UI_Shutdown
  &UI_UpdateMenu,      // UI_UpdateMenu
  &UI_KeyEvent,        // UI_KeyEvent
  &UI_MouseMove,       // UI_MouseMove
  &UI_SetActiveMenu,   // UI_SetActiveMenu
  &UI_AddServerToList, // UI_AddServerToList
  &UI_GetCursorPos,    // UI_GetCursorPos
  &UI_SetCursorPos,    // UI_SetCursorPos
  &UI_ShowCursor,      // UI_ShowCursor
  &UI_CharEvent,       // UI_CharEvent
  &UI_MouseInRect,     // UI_MouseInRect
  &UI_IsVisible,       // UI_IsVisible
  &UI_CreditsActive,   // UI_CreditsActive
  &UI_FinalCredits,    // UI_FinalCredits
};

extern "C" EXPORT int GetMenuAPI(UI_FUNCTIONS *pFunctionTable, ui_enginefuncs_t *pEngfuncsFromEngine, ui_globalvars_t *pGlobals) {
  if (!pFunctionTable || !pEngfuncsFromEngine) {
    return false;
  }

  memcpy(pFunctionTable, &exportedUIFunctions, sizeof(UI_FUNCTIONS));

  // save ptr
  engineFunctions = pEngfuncsFromEngine;
  globalVars = pGlobals;

  return true;
}

static UI_EXTENDED_FUNCTIONS exportedExtendedTable = {
  AddTouchButtonToList,                   // AddTouchButtonToList
  &UI_MenuResetPing_f,                    // UI_MenuResetPing_f
  &UI_ConnectionWarning_f,                // UI_ConnectionWarning_f
  &UI_UpdateDialog,                       // UI_UpdateDialog
  &UI_ShowMessageBox,                     // UI_ShowMessageBox
  &UI_ConnectionProgress_Disconnect,      // UI_ConnectionProgress_Disconnect
  &UI_ConnectionProgress_Download,        // UI_ConnectionProgress_Download
  &UI_ConnectionProgress_DownloadEnd,     // UI_ConnectionProgress_DownloadEnd
  &UI_ConnectionProgress_Precache,        // UI_ConnectionProgress_Precache
  &UI_ConnectionProgress_Connect,         // UI_ConnectionProgress_Connect
  &UI_ConnectionProgress_ChangeLevel,     // UI_ConnectionProgress_ChangeLevel
  &UI_ConnectionProgress_ParseServerInfo, // UI_ConnectionProgress_ParseServerInfo
};

extern "C" EXPORT int GetExtAPI(int version, UI_EXTENDED_FUNCTIONS *pFunctionTable, ui_extendedfuncs_t *pEngfuncsFromEngine) {
  if (!pFunctionTable || !pEngfuncsFromEngine)
    return false;

  if (version != MENU_EXTENDED_API_VERSION) {
    mcr_ConsoleDebugLog(
      "failed to initialize extended menu API. From engine: %i, target: %i\n",
      version, MENU_EXTENDED_API_VERSION);

    return false;
  }

  memcpy(pFunctionTable, &exportedExtendedTable, sizeof(UI_EXTENDED_FUNCTIONS));

  // save ptr
  extendedFunctions = pEngfuncsFromEngine;

  return true;
}

// FUNCTION_EXPORTING.cpp
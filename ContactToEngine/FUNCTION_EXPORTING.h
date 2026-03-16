
#pragma once

#include "extdll_menu.h"

// UI_FUNCTIONS
extern void UI_Shutdown();
extern void UI_UpdateMenu(float flTime);
extern void UI_KeyEvent(int key, int down);

extern void UI_SetActiveMenu(int active);
extern void UI_AddServerToList(netadr_s adr, const char *info);
extern void UI_GetCursorPos(int *pos_x, int *pos_y);
extern void UI_SetCursorPos(int pos_x, int pos_y);
extern void UI_ShowCursor(int show);
extern void UI_CharEvent(int key);
extern int UI_MouseInRect(void);
extern int UI_IsVisible(void);
extern int UI_CreditsActive(void);
extern void UI_FinalCredits(void);

// UI_EXTENDED_FUNCTIONS
extern "C" EXPORT void AddTouchButtonToList(const char *name, const char *texture, const char *command, unsigned char *color, int flags);
extern void UI_MenuResetPing_f(void);
extern void UI_ConnectionWarning_f(void);
extern void UI_UpdateDialog(int preferStore);
extern void UI_ShowMessageBox(const char *text);

extern void UI_ConnectionProgress_Disconnect(void);
extern void UI_ConnectionProgress_Download(const char *pszFileName, const char *pszServerName, int iCurrent, int iTotal, const char *comment);
extern void UI_ConnectionProgress_DownloadEnd(void);
extern void UI_ConnectionProgress_Precache(void);
extern void UI_ConnectionProgress_Connect(const char *server); // NULL for local server
extern void UI_ConnectionProgress_ChangeLevel(void);
extern void UI_ConnectionProgress_ParseServerInfo(const char *server);

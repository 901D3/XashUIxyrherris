/**
 * MenusExport.h - exports menus
 */

#include "Menus/MenuBase.h" // UIMenu

extern UIMenu menuMain;

// SETTINGS
extern UIMenu menuSettings;
extern UIMenu menuSettingsControls;
extern UIMenu menuSettingsAdvControls;

extern UIMenu menuSettingsAudio;
extern UIMenu menuSettingsVideo;

extern void menuMainInit();
extern void menuMainRenderWrapper();

extern void menuSettingsInit();
extern void menuSettingsRenderWrapper();

extern void menuSettingsControlsInit();
extern void menuSettingsControlsRenderWrapper();

extern void menuSettingsAdvControlsInit();
extern void menuSettingsAdvControlsRenderWrapper();

extern void menuSettingsAudioInit();
extern void menuSettingsAudioRenderWrapper();

extern void menuSettingsVideoInit();
extern void menuSettingsVideoRenderWrapper();

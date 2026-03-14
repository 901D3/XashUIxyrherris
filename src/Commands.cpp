
#include "Base.h"
#include "Commands.h"
#include "EngineStuff.h"
#include "Menus/UpdateElement.h"

#include "Utils/Utils.h"

// xashuixyr_element_mouse_events_reset
static void elementMouseEventsResetWrapper() {
  elementMouseEventsReset();
}

// xashuixyr_mouse_events_log
static void mouseEventsLogWrapper() {
  mouseEventsLog();
}

// xashuixyr_mouse_events_reset
static void mouseEventsResetWrapper() {
  mouseEventsReset();
}

void commandsInit() {
  engineFunctions->pfnAddCommand("xashuixyr_element_mouse_events_reset", &elementMouseEventsResetWrapper);
  engineFunctions->pfnAddCommand("xashuixyr_mouse_events_log", &mouseEventsLogWrapper);
  engineFunctions->pfnAddCommand("xashuixyr_mouse_events_reset", &mouseEventsResetWrapper);
}

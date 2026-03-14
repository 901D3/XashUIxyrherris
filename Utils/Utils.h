
#pragma once

#include <string.h>
#include "EngineStuff.h"

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__))

#define mcr_ConsoleDebugLog(fmt, ...) ( \
  engineFunctions->Con_Printf( \
    "[%s/%s:%i]>" fmt "\n", \
    __FILENAME__, \
    __func__, \
    __LINE__, \
    ##__VA_ARGS__))

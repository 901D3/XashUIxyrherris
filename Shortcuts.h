
#pragma once

#include "EngineStuff.h"

#define mcr_ENGINE_MEM_ALLOC(length) (engineFunctions->pfnMemAlloc(length, __FILE__, __LINE__))
#define mcr_ENGINE_MEM_FREE(ptr) (engineFunctions->pfnMemFree(ptr, __FILE__, __LINE__))

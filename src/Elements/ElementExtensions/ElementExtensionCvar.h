
#pragma once

#include "Elements/ElementBase.h"

typedef enum {
  CVAR_VALUE_TYPE_INT = 0,
  CVAR_VALUE_TYPE_UINT,
  CVAR_VALUE_TYPE_LONGLONG,
  CVAR_VALUE_TYPE_ULONGLONG,
  CVAR_VALUE_TYPE_BOOLEAN,
  CVAR_VALUE_TYPE_FLOAT,
  CVAR_VALUE_TYPE_STRING
} CvarValueType;

class UIElementExtensionCvar {
public:
  UIElementExtensionCvar();
  virtual ~UIElementExtensionCvar();

  char *cvar;
  CvarValueType cvarValueType;

  virtual void bindCvar(const char *cvarName);
  virtual void freeCvar();

  virtual void setCvarString(const char *string);
  virtual void getCvarValue(void *output);
};

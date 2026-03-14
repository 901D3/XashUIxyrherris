
#include <stddef.h>

#include "Elements/ElementExtensions/ElementExtensionCvar.h"
#include "Utils/ConvertUtils.h"
#include "Utils/Shortcuts.h"

UIElementExtensionCvar::UIElementExtensionCvar() {
  cvar = nullptr;
  cvarValueType = CVAR_VALUE_TYPE_INT;
}

UIElementExtensionCvar::~UIElementExtensionCvar() {
  freeCvar();
}

void UIElementExtensionCvar::bindCvar(const char *cvarName) {
  if (!cvarName) {
    mcr_ConsoleDebugLog("Invalid cvar name");
    return;
  }

  freeCvar();

  size_t length = strlen(cvarName) + 1;

  cvar = static_cast<char *>(mcr_ENGINE_MEM_ALLOC(length));
  memcpy(cvar, cvarName, length);
}

inline void UIElementExtensionCvar::freeCvar() {
  if (cvar)
    mcr_ENGINE_MEM_FREE(cvar);
}

inline void UIElementExtensionCvar::setCvarString(const char *string) {
  if (!string) {
    mcr_ConsoleDebugLog("Invalid string");
    return;
  }

  engineFunctions->pfnCvarSetString(cvar, string);
}

inline void UIElementExtensionCvar::getCvarValue(void *output) {
  const char *string = engineFunctions->pfnGetCvarString(cvar);

  if (cvarValueType == CVAR_VALUE_TYPE_INT)
    *(static_cast<int *>(output)) = ConvertUtils::fastAToInt<int>(string);

  else if (cvarValueType == CVAR_VALUE_TYPE_UINT)
    *(static_cast<unsigned int *>(output)) = ConvertUtils::fastAToInt<unsigned int>(string);

  else if (cvarValueType == CVAR_VALUE_TYPE_LONGLONG)
    *(static_cast<long long *>(output)) = ConvertUtils::fastAToInt<long long>(string);

  else if (cvarValueType == CVAR_VALUE_TYPE_ULONGLONG)
    *(static_cast<unsigned long long *>(output)) = ConvertUtils::fastAToInt<unsigned long long>(string);

  else if (cvarValueType == CVAR_VALUE_TYPE_BOOLEAN)
    *(static_cast<bool *>(output)) = (*string == '1');

  else if (cvarValueType == CVAR_VALUE_TYPE_FLOAT)
    *(static_cast<float *>(output)) = ConvertUtils::fastAToFloat<float>(string);

  else if (cvarValueType == CVAR_VALUE_TYPE_STRING)
    *(static_cast<const char **>(output)) = string;
}

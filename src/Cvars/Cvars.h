
#pragma once

#include <stdint.h> // uintptr_t

#include "cvardef.h" // cvar_t, FCVAR enums

#include "Cvars/CvarAdditionalDefs.h"

#include "Managers/Font/FontDefs.h"             // FontEnums
#include "Managers/Background/BackgroundDefs.h" // BackgroundTransformStyleEnums

#include "Primitives/Function.h" // PtrToVoidFunction

// UI only vars
typedef struct {
  CvarMirror<bool, 2> xashuixyr_process_next_frame;

  CvarMirror<int, 8> xashuixyr_base_width;
  CvarMirror<int, 8> xashuixyr_base_height;

  CvarMirror<bool, 2> xashuixyr_draw_background;
  CvarMirror<BackgroundTransformStyleEnums, 4> xashuixyr_background_transform_style;

  CvarMirror<unsigned char, 4> xashuixyr_background_r;
  CvarMirror<unsigned char, 4> xashuixyr_background_g;
  CvarMirror<unsigned char, 4> xashuixyr_background_b;
  CvarMirror<unsigned char, 4> xashuixyr_background_a;

  CvarMirror<int, 8> xashuixyr_background_x;
  CvarMirror<int, 8> xashuixyr_background_y;
  CvarMirror<int, 8> xashuixyr_background_width;
  CvarMirror<int, 8> xashuixyr_background_height;

  CvarMirror<int, 8> xashuixyr_background_crop_left;
  CvarMirror<int, 8> xashuixyr_background_crop_top;
  CvarMirror<int, 8> xashuixyr_background_crop_right;
  CvarMirror<int, 8> xashuixyr_background_crop_bottom;

  CvarMirror<int, 8> xashuixyr_bound_x;
  CvarMirror<int, 8> xashuixyr_bound_y;

  CvarMirror<FontEnums, 4> xashuixyr_font;
} CvarMirrors;

extern CvarMirrors cvarMirrors;

//----------
extern cvar_t *xashuixyr_base_width;
extern cvar_t *xashuixyr_base_height;

extern cvar_t *xashuixyr_draw_background;

extern cvar_t *xashuixyr_background_transform_style;

extern cvar_t *xashuixyr_background_r;
extern cvar_t *xashuixyr_background_g;
extern cvar_t *xashuixyr_background_b;
extern cvar_t *xashuixyr_background_a;

extern cvar_t *xashuixyr_background_x;
extern cvar_t *xashuixyr_background_y;
extern cvar_t *xashuixyr_background_width;
extern cvar_t *xashuixyr_background_height;

extern cvar_t *xashuixyr_background_crop_left;
extern cvar_t *xashuixyr_background_crop_top;
extern cvar_t *xashuixyr_background_crop_right;
extern cvar_t *xashuixyr_background_crop_bottom;

extern cvar_t *xashuixyr_bound_x;
extern cvar_t *xashuixyr_bound_y;

extern cvar_t *xashuixyr_font;
//----------

template <typename T, int stringLength>
inline void setCvarMirror(CvarMirror<T, stringLength> &cvarMirror, const char *string) {
  if (strcmp(cvarMirror.string, string) != 0) {
    memcpy(cvarMirror.string, string, stringLength);

    cvarMirror.value = ConvertUtils::fastAToInt<T>(string);
  }
}

template <typename T, int stringLength>
inline void setCvarMirrorEnum(CvarMirror<T, stringLength> &cvarMirror, const char *string) {
  if (strcmp(cvarMirror.string, string) != 0) {
    memcpy(cvarMirror.string, string, stringLength);

    cvarMirror.value = ConvertUtils::fastAToEnum<T>(string);
  }
}

template <typename T, int stringLength>
inline void setCvarMirrorWithCallBack(CvarMirror<T, stringLength> &cvarMirror, const char *string, PtrToVoidFunction callback) {
  if (strcmp(cvarMirror.string, string) != 0) {
    memcpy(cvarMirror.string, string, stringLength);

    cvarMirror.value = ConvertUtils::fastAToInt<T>(string);
    callback();
  }
}

template <typename T, int stringLength>
inline void setCvarMirrorEnumWithCallBack(CvarMirror<T, stringLength> &cvarMirror, const char *string, PtrToVoidFunction callback) {
  if (strcmp(cvarMirror.string, string) != 0) {
    memcpy(cvarMirror.string, string, stringLength);

    cvarMirror.value = ConvertUtils::fastAToEnum<T>(string);
    callback();
  }
}

// used for "when the UI set cvars" case
extern void setCvar(cvar_t *cvar, const char *string);

// used for "when user set cvars" case
extern void syncCvarMirrors();

extern void cvarsInit();

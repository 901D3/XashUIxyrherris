
#include "Cvars/Cvars.h"

#include "Managers/Background/Background.h" // BackgroundTransformStyleEnums, bitmapBackgroundTransformStyleSwitch
#include "Managers/Font/FontDefs.h"         // FontEnums
#include "Utils/ConvertUtils.h"             // ConvertUtils
#include "Utils/MathUtils.h"                // mcr_clampUint8

CvarMirrors cvarMirrors;

cvar_t *xashuixyr_process_next_frame;
cvar_t *xashuixyr_base_width;
cvar_t *xashuixyr_base_height;
cvar_t *xashuixyr_draw_background;
cvar_t *xashuixyr_background_transform_style;
cvar_t *xashuixyr_background_r;
cvar_t *xashuixyr_background_g;
cvar_t *xashuixyr_background_b;
cvar_t *xashuixyr_background_a;
cvar_t *xashuixyr_background_x;
cvar_t *xashuixyr_background_y;
cvar_t *xashuixyr_background_width;
cvar_t *xashuixyr_background_height;
cvar_t *xashuixyr_background_crop_left;
cvar_t *xashuixyr_background_crop_top;
cvar_t *xashuixyr_background_crop_right;
cvar_t *xashuixyr_background_crop_bottom;
cvar_t *xashuixyr_bound_x;
cvar_t *xashuixyr_bound_y;
cvar_t *xashuixyr_font;

void setCvar(cvar_t *cvar, const char *string) {
  int newValue = ConvertUtils::fastAToInt<int>(string);

  if (cvar == xashuixyr_process_next_frame)
    cvarMirrors.xashuixyr_process_next_frame.value = static_cast<bool>(newValue);
  else if (cvar == xashuixyr_base_width)
    cvarMirrors.xashuixyr_base_width.value = mcr_max(newValue, 0);
  else if (cvar == xashuixyr_base_height)
    cvarMirrors.xashuixyr_base_height.value = mcr_max(newValue, 0);
  else if (cvar == xashuixyr_draw_background)
    cvarMirrors.xashuixyr_draw_background.value = !!newValue;
  else if (cvar == xashuixyr_background_transform_style) {
    cvarMirrors.xashuixyr_background_transform_style.value = static_cast<BackgroundTransformStyleEnums>(newValue);
    bitmapBackgroundTransformStyleSwitch();
  } else if (cvar == xashuixyr_background_r)
    cvarMirrors.xashuixyr_background_r.value = mcr_clampUint8(newValue);
  else if (cvar == xashuixyr_background_g)
    cvarMirrors.xashuixyr_background_g.value = mcr_clampUint8(newValue);
  else if (cvar == xashuixyr_background_b)
    cvarMirrors.xashuixyr_background_b.value = mcr_clampUint8(newValue);
  else if (cvar == xashuixyr_background_a)
    cvarMirrors.xashuixyr_background_a.value = mcr_clampUint8(newValue);
  else if (cvar == xashuixyr_background_x)
    cvarMirrors.xashuixyr_background_x.value = newValue;
  else if (cvar == xashuixyr_background_y)
    cvarMirrors.xashuixyr_background_y.value = newValue;
  else if (cvar == xashuixyr_background_width)
    cvarMirrors.xashuixyr_background_width.value = newValue;
  else if (cvar == xashuixyr_background_height)
    cvarMirrors.xashuixyr_background_height.value = newValue;
  else if (cvar == xashuixyr_background_crop_left)
    cvarMirrors.xashuixyr_background_crop_left.value = newValue;
  else if (cvar == xashuixyr_background_crop_top)
    cvarMirrors.xashuixyr_background_crop_top.value = newValue;
  else if (cvar == xashuixyr_background_crop_right)
    cvarMirrors.xashuixyr_background_crop_right.value = newValue;
  else if (cvar == xashuixyr_background_crop_bottom)
    cvarMirrors.xashuixyr_background_crop_bottom.value = newValue;
  else if (cvar == xashuixyr_bound_x)
    cvarMirrors.xashuixyr_bound_x.value = newValue;
  else if (cvar == xashuixyr_bound_y)
    cvarMirrors.xashuixyr_bound_y.value = newValue;
  else if (cvar == xashuixyr_font)
    cvarMirrors.xashuixyr_font.value = static_cast<FontEnums>(newValue);

  engineFunctions->pfnCvarSetString(cvar->name, string);
}

inline void syncCvarMirrors() {
  setCvarMirror(cvarMirrors.xashuixyr_process_next_frame, xashuixyr_process_next_frame->string);
  setCvarMirror(cvarMirrors.xashuixyr_base_width, xashuixyr_base_width->string);
  setCvarMirror(cvarMirrors.xashuixyr_base_height, xashuixyr_base_height->string);
  setCvarMirror(cvarMirrors.xashuixyr_draw_background, xashuixyr_draw_background->string);
  setCvarMirrorEnumWithCallBack(
    cvarMirrors.xashuixyr_background_transform_style,
    xashuixyr_background_transform_style->string,
    bitmapBackgroundTransformStyleSwitch);
  setCvarMirror(cvarMirrors.xashuixyr_background_r, xashuixyr_background_r->string);
  setCvarMirror(cvarMirrors.xashuixyr_background_g, xashuixyr_background_g->string);
  setCvarMirror(cvarMirrors.xashuixyr_background_b, xashuixyr_background_b->string);
  setCvarMirror(cvarMirrors.xashuixyr_background_a, xashuixyr_background_a->string);
  setCvarMirror(cvarMirrors.xashuixyr_background_x, xashuixyr_background_x->string);
  setCvarMirror(cvarMirrors.xashuixyr_background_y, xashuixyr_background_y->string);
  setCvarMirror(cvarMirrors.xashuixyr_background_width, xashuixyr_background_width->string);
  setCvarMirror(cvarMirrors.xashuixyr_background_height, xashuixyr_background_height->string);
  setCvarMirror(cvarMirrors.xashuixyr_background_crop_left, xashuixyr_background_crop_left->string);
  setCvarMirror(cvarMirrors.xashuixyr_background_crop_top, xashuixyr_background_crop_top->string);
  setCvarMirror(cvarMirrors.xashuixyr_background_crop_right, xashuixyr_background_crop_right->string);
  setCvarMirror(cvarMirrors.xashuixyr_background_crop_bottom, xashuixyr_background_crop_bottom->string);
  setCvarMirror(cvarMirrors.xashuixyr_bound_x, xashuixyr_bound_x->string);
  setCvarMirror(cvarMirrors.xashuixyr_bound_y, xashuixyr_bound_y->string);
  setCvarMirrorEnum(cvarMirrors.xashuixyr_font, xashuixyr_font->string);
}

inline void cvarsInit() {
  xashuixyr_process_next_frame = engineFunctions->pfnRegisterVariable("xashuixyr_process_next_frame", "1", FCVAR_ARCHIVE);

  xashuixyr_base_width = engineFunctions->pfnRegisterVariable("xashuixyr_base_width", "1024", FCVAR_ARCHIVE);
  xashuixyr_base_height = engineFunctions->pfnRegisterVariable("xashuixyr_base_height", "768", FCVAR_ARCHIVE);

  xashuixyr_draw_background = engineFunctions->pfnRegisterVariable("xashuixyr_draw_background", "1", FCVAR_ARCHIVE);

  xashuixyr_background_transform_style = engineFunctions->pfnRegisterVariable("xashuixyr_background_transform_style", "4", FCVAR_ARCHIVE);

  xashuixyr_background_r = engineFunctions->pfnRegisterVariable("xashuixyr_background_r", "255", FCVAR_ARCHIVE);
  xashuixyr_background_g = engineFunctions->pfnRegisterVariable("xashuixyr_background_g", "255", FCVAR_ARCHIVE);
  xashuixyr_background_b = engineFunctions->pfnRegisterVariable("xashuixyr_background_b", "255", FCVAR_ARCHIVE);
  xashuixyr_background_a = engineFunctions->pfnRegisterVariable("xashuixyr_background_a", "255", FCVAR_ARCHIVE);

  xashuixyr_bound_x = engineFunctions->pfnRegisterVariable("xashuixyr_bound_x", "1024", FCVAR_ARCHIVE);
  xashuixyr_bound_y = engineFunctions->pfnRegisterVariable("xashuixyr_bound_y", "768", FCVAR_ARCHIVE);

  xashuixyr_font = engineFunctions->pfnRegisterVariable("xashuixyr_font", "0", FCVAR_ARCHIVE); // follow FontEnums

  xashuixyr_background_x = engineFunctions->pfnRegisterVariable("xashuixyr_background_x", "0", FCVAR_ARCHIVE);
  xashuixyr_background_y = engineFunctions->pfnRegisterVariable("xashuixyr_background_y", "0", FCVAR_ARCHIVE);
  xashuixyr_background_width = engineFunctions->pfnRegisterVariable("xashuixyr_background_width", "0", FCVAR_ARCHIVE);
  xashuixyr_background_height = engineFunctions->pfnRegisterVariable("xashuixyr_background_height", "0", FCVAR_ARCHIVE);

  xashuixyr_background_crop_left = engineFunctions->pfnRegisterVariable("xashuixyr_background_crop_left", "0", FCVAR_ARCHIVE);
  xashuixyr_background_crop_top = engineFunctions->pfnRegisterVariable("xashuixyr_background_crop_top", "0", FCVAR_ARCHIVE);
  xashuixyr_background_crop_right = engineFunctions->pfnRegisterVariable("xashuixyr_background_crop_right", "0", FCVAR_ARCHIVE);
  xashuixyr_background_crop_bottom = engineFunctions->pfnRegisterVariable("xashuixyr_background_crop_bottom", "0", FCVAR_ARCHIVE);
}
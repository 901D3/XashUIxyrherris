
#pragma once

#include "Base.h"

#define mcr_scaleWidth(width) (((width) * globalUIContext.displayWidth) / globalUIContext.baseWidth)
#define mcr_scaleHeight(height) (((height) * globalUIContext.displayHeight) / globalUIContext.baseHeight)

#define mcr_unscaleWidth(scaledWidth) (((scaledWidth) * globalUIContext.baseWidth) / globalUIContext.displayWidth)
#define mcr_unscaleHeight(scaledHeight) (((scaledHeight) * globalUIContext.baseHeight) / globalUIContext.displayHeight)

#define mcr_shiftX(x) ((mcr_scaleWidth(x)) + globalUIContext.shiftX)
#define mcr_shiftY(y) ((mcr_scaleHeight(y)) + globalUIContext.shiftY)


#include "Primitives/Transform.h"

#include "Presets/PresetsTransform.h"

void buttonAlignmentGenerateList(
  Position *positions,
  int offsetX,
  int offsetY,
  int spaceX,
  int spaceY,
  const int count) {
  for (int i = 0; i < count; i++) {
    positions[i].x = offsetX + i * spaceX;
    positions[i].y = offsetY + i * spaceY;
  }
}

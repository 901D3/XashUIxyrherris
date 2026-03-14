/**
 * Tricks.h - UI tricks
 */

#pragma once

typedef struct {
  // mouse event revalidation only(usually after close console)
  int mouseMoveGeneration;       // incremented by input system
  int lastProcessedMouseMoveGen; // last generation consumed by UI
  // should not be used for other purposes

} Tricks; // intentionally named it "Tricks"

extern Tricks globalTricks;

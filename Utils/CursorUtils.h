
#pragma once

namespace CursorUtils {

  inline bool isMouseInRect(
    int x, int y,
    int width, int height,
    int mouseX, int mouseY) {
    return (mouseX >= x && mouseX < x + width &&
            mouseY >= y && mouseY < y + height);
  }

  inline bool isMouseDown() { // mouseDown = 1, lastMouseDown = 0 | when LMB is down and previously isn't
    return (globalUIMouseContext.mouseDown && !globalUIMouseContext.lastMouseDown);
  }

  inline bool isMouseHold() { // mouseDown = 1, lastMouseDown = 1 | when LMB is down and previously is
    return (globalUIMouseContext.mouseDown && globalUIMouseContext.lastMouseDown);
  }

  inline bool isMouseUp() { // mouseDown = 0, lastMouseDown = 1 | when LMB is up and previously isn't
    return (!globalUIMouseContext.mouseDown && globalUIMouseContext.lastMouseDown);
  }

  inline bool isMouseIdle() { // mouseDown = 0, lastMouseDown = 1 | when LMB is up and previously is
    return (!globalUIMouseContext.mouseDown && !globalUIMouseContext.lastMouseDown);
  }

  // no smoothing mouse move
  inline bool isMouseMoveStart() {
    return (globalUIMouseContext.mouseMove && !globalUIMouseContext.lastMouseMove);
  }

  inline bool isMouseMoving() {
    return (globalUIMouseContext.mouseMove && globalUIMouseContext.lastMouseMove);
  }

  inline bool isMouseMoveEnd() {
    return (!globalUIMouseContext.mouseMove && globalUIMouseContext.lastMouseMove);
  }

  inline bool isMouseNotMoving() {
    return (!globalUIMouseContext.mouseMove && !globalUIMouseContext.lastMouseMove);
  }

} // namespace CursorUtils

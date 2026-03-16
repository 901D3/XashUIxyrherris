
#pragma once

namespace CursorUtils {

  inline bool isMouseInRect(
    int x, int y,
    int width, int height,
    int mouseX, int mouseY) {

    return (
      mouseX >= x && mouseX < x + width
      && mouseY >= y && mouseY < y + height);
  }

  // mouseDown = 1, lastMouseDown = 0 | when LMB is down and previously isn't
  inline bool isMouseDown(bool mouseDown, bool lastMouseDown) {
    return (mouseDown && !lastMouseDown);
  }

  // mouseDown = 1, lastMouseDown = 1 | when LMB is down and previously is
  inline bool isMouseHold(bool mouseDown, bool lastMouseDown) {
    return (mouseDown && lastMouseDown);
  }

  // mouseDown = 0, lastMouseDown = 1 | when LMB is up and previously isn't
  inline bool isMouseUp(bool mouseDown, bool lastMouseDown) {
    return (!mouseDown && lastMouseDown);
  }

  // mouseDown = 0, lastMouseDown = 1 | when LMB is up and previously is
  inline bool isMouseIdle(bool mouseDown, bool lastMouseDown) {
    return (!mouseDown && !lastMouseDown);
  }

  // no smoothing mouse move
  inline bool isMouseMoveStart(bool mouseMove, bool lastMouseMove) {
    return (mouseMove && !lastMouseMove);
  }

  inline bool isMouseMoving(bool mouseMove, bool lastMouseMove) {
    return (mouseMove && lastMouseMove);
  }

  inline bool isMouseMoveEnd(bool mouseMove, bool lastMouseMove) {
    return (!mouseMove && lastMouseMove);
  }

  inline bool isMouseNotMoving(bool mouseMove, bool lastMouseMove) {
    return (!mouseMove && !lastMouseMove);
  }

} // namespace CursorUtils

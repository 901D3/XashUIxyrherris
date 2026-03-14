
#pragma once

template <typename T, int StringLength>
struct CvarMirror {
  char string[StringLength];
  T value{};
};

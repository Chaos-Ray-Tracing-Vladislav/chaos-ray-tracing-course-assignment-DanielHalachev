#pragma once
#include <ostream>
struct Color {
  static const Color black;
  static const Color white;
  static Color randomColor();

  unsigned short red;
  unsigned short green;
  unsigned short blue;

  Color();
  Color(unsigned short red, unsigned short green, unsigned short blue);

  friend std::ostream &operator<<(std::ostream &os, const struct Color &color);
};
#pragma once
#include <ostream>
struct Color {
  unsigned short red;
  unsigned short green;
  unsigned short blue;
  Color(unsigned short red, unsigned short green, unsigned short blue) : red(red), green(green), blue(blue){};
  friend std::ostream &operator<<(std::ostream &os, const struct Color &color) {
    os << color.red << " " << color.green << " " << color.blue;
    return os;
  }
};
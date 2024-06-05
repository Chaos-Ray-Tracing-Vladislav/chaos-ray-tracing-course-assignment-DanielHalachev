#ifndef COLOR_H
#define COLOR_H
#include <ostream>
struct Color {
  unsigned short red;
  unsigned short green;
  unsigned short blue;
  friend std::ostream &operator<<(std::ostream &os, const struct Color &color) {
    os << color.red << " " << color.green << " " << color.blue;
    return os;
  }
};
#endif  // COLOR_H
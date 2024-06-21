#include "tracer/Utils.h"

#include <algorithm>

#include "tracer/Vector.h"

PPMColor::PPMColor(const Color &color) {
  this->red = static_cast<unsigned short>(std::clamp(0.0f, 1.0f, color[0]) * 255);
  this->green = static_cast<unsigned short>(std::clamp(0.0f, 1.0f, color[1]) * 255);
  this->blue = static_cast<unsigned short>(std::clamp(0.0f, 1.0f, color[2]) * 255);
}

std::ostream &operator<<(std::ostream &os, const struct PPMColor &color) {
  os << color.red << " " << color.green << " " << color.blue;
  return os;
}

Texture::Texture() : color{Color::generateRandom()}, albedo{0.18f, 0.18f, 0.18f} {};

Texture::Texture(const Color &color, const Vector &albedo) : color{color}, albedo{albedo} {};
#include "tracer/Utils.h"

#include <algorithm>
#include <random>

#include "tracer/Vector.h"

const Color Color::black = {0.0f, 0.0f, 0.0f};
const Color Color::white = {1.0f, 1.0f, 1.0f};

Color Color::randomColor() {
  std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
  std::mt19937 rng(std::random_device{}());
  return Color(distribution(rng), distribution(rng), distribution(rng));
}

Color::Color() : red{0.0f}, green{0.0f}, blue{0.0f} {};

Color::Color(const Vector &rgb) : red{rgb[0]}, green{rgb[1]}, blue{rgb[2]} {};

Color::Color(float red, float green, float blue) : red{red}, green{green}, blue{blue} {};

PPMColor::PPMColor(const Color &color) {
  this->red = static_cast<unsigned short>(std::clamp(0.0f, 1.0f, color.red) * 255);
  this->green = static_cast<unsigned short>(std::clamp(0.0f, 1.0f, color.green) * 255);
  this->blue = static_cast<unsigned short>(std::clamp(0.0f, 1.0f, color.blue) * 255);
}

std::ostream &operator<<(std::ostream &os, const struct PPMColor &color) {
  os << color.red << " " << color.green << " " << color.blue;
  return os;
}

Texture::Texture() : color{Color::randomColor()}, albedo{0.18f, 0.18f, 0.18f} {};

Texture::Texture(const Color &color, const Vector &albedo) : color{color}, albedo{albedo} {};
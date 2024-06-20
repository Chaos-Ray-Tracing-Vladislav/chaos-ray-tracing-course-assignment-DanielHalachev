#include "tracer/Utils.h"

#include <random>

const Color Color::black = {0, 0, 0};
const Color Color::white = {255, 255, 255};

Color Color::randomColor() {
  std::uniform_int_distribution<unsigned short> distribution(0, 255);
  std::mt19937 rng(std::random_device{}());
  return Color(distribution(rng), distribution(rng), distribution(rng));
}

Color::Color() : red{0}, green{0}, blue{0} {};

Color::Color(unsigned short red, unsigned short green, unsigned short blue) : red{red}, green{green}, blue{blue} {};

std::ostream &operator<<(std::ostream &os, const struct Color &color) {
  os << color.red << " " << color.green << " " << color.blue;
  return os;
}
#pragma once
#include <ostream>

#include "tracer/Vector.h"

struct Color {
  static const Color black;
  static const Color white;
  static Color randomColor();

  float red;
  float green;
  float blue;

  Color();
  explicit Color(const Vector &rgb);
  Color(float red, float green, float blue);
};

struct PPMColor {
  unsigned short red;
  unsigned short green;
  unsigned short blue;
  explicit PPMColor(const Color &color);
  friend std::ostream &operator<<(std::ostream &os, const struct PPMColor &color);
};

struct Texture {
  Color color;
  Vector albedo;

  Texture();
  Texture(const Color &color, const Vector &albedo);
};
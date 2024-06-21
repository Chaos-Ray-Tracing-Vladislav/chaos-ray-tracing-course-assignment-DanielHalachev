#pragma once
#include <array>

#include "Vector.h"
#include "tracer/Utils.h"

#define TRIANGLE_NUM_VERTICES 3
#define SHADOW_BIAS 0.0001f

struct Light;

class Triangle {
 private:
  std::array<Vector, TRIANGLE_NUM_VERTICES> vertices;
  Texture texture;
  Vector normal;
  Vector calculateNormal() const;

 public:
  Triangle();
  explicit Triangle(const std::array<Vector, 3> &vertices);
  Vector &operator[](unsigned short i);
  const Texture &getTexture() const;
  Texture &setTexture();
  const Vector &operator[](unsigned short i) const;
  const Vector &getTriangleNormal() const;
  float area() const;
};
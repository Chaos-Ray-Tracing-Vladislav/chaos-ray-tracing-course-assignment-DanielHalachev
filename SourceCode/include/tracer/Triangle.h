#pragma once
#include <array>

#include "Vector.h"
#include "tracer/Utils.h"

#define TRIANGLE_NUM_VERTICES 3
#define SHADOW_BIAS 0.0001f

struct Light;

struct Triangle {
 private:
  std::array<Vector, TRIANGLE_NUM_VERTICES> vertices;
  Vector normal;
  Vector getNormal() const;

 public:
  Texture texture;
  Triangle();
  explicit Triangle(std::array<Vector, 3> &vertices);
  Vector &operator[](unsigned short i);
  const Vector &operator[](unsigned short i) const;
  Vector getTriangleNormal() const;
  float area() const;
};
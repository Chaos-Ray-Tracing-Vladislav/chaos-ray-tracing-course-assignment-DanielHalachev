#pragma once
#include <array>

#include "Vector.h"

#define TRIANGLE_NUM_VERTICES 3
class Triangle {
 private:
  std::array<Vector, TRIANGLE_NUM_VERTICES> vertices;

 public:
  Triangle();
  explicit Triangle(std::array<Vector, 3> &vertices);
  Vector getTriangleNormal() const;
  float area() const;
};
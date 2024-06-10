#pragma once
#include <array>

#include "Ray.h"

#define DIMENSION 3
class Triangle {
 private:
  std::array<Vector, DIMENSION> vertices;

 public:
  Triangle();
  explicit Triangle(std::array<Vector, 3> &vertices);
  Vector normalVector() const;
  float area() const;
};
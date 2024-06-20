#pragma once
#include <array>
#include <istream>

#include "Vector.h"
#include "tracer/Utils.h"

#define TRIANGLE_NUM_VERTICES 3
struct Triangle {
 private:
  std::array<Vector, TRIANGLE_NUM_VERTICES> vertices;
  Vector normal;
  Vector getNormal() const;

 public:
  Color color;
  Triangle();
  explicit Triangle(std::array<Vector, 3> &vertices);
  Vector &operator[](unsigned short i);
  const Vector &operator[](unsigned short i) const;
  friend std::istream &operator>>(std::istream &is, Triangle &triangle);
  Vector getTriangleNormal() const;
  float area() const;
};
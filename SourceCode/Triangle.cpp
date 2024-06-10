#include "Triangle.h"

#include <algorithm>
#include <array>
#include <random>

#include "Ray.h"

Triangle::Triangle() = default;
Triangle::Triangle(std::array<Vector, 3> &vertices) : vertices(vertices) {
  // I am not sure if this is the right thing to do this
  float slope = (this->vertices[1].x - this->vertices[0].x) * (this->vertices[2].y - this->vertices[0].y) -
                (this->vertices[1].y - this->vertices[0].y) * (this->vertices[2].x - this->vertices[0].x);
  while (slope < 0) {
    std::shuffle(this->vertices.begin(), this->vertices.end(), std::mt19937());
    slope = (this->vertices[1].y - this->vertices[0].y) * (this->vertices[2].x - this->vertices[1].x) -
            (this->vertices[1].x - this->vertices[0].x) * (this->vertices[2].y - this->vertices[1].y);
  }
  // std::sort(vertices.begin(), vertices.end(), [](const Vector &a, const Vector &b) { return a.x < b.x; });
  // if (this->vertices[1].y > this->vertices[2].y) {
  //   std::swap(this->vertices[1], this->vertices[2]);
  // }
}

Vector Triangle::normalVector() const {
  Vector v1 = this->vertices[1] - this->vertices[0];
  Vector v2 = this->vertices[2] - this->vertices[0];
  return v1 * v2;
}

float Triangle::area() const {
  return this->normalVector().length() / 2;
}
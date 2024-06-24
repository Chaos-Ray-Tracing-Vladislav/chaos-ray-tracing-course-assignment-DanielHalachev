#include <tracer/Triangle.h>

#include <array>

#include "tracer/Utils.h"
#include "tracer/Vector.h"

Triangle::Triangle() = default;
Triangle::Triangle(const std::array<Vector, 3> &vertices) : vertices(vertices), texture(Texture()) {
  // I am not sure if this is the right way to do this
  // float slope = (this->vertices[1][0] - this->vertices[0][0]) * (this->vertices[2][1] - this->vertices[0][1]) -
  //               (this->vertices[1][1] - this->vertices[0][1]) * (this->vertices[2][0] - this->vertices[0][0]);
  // while (slope < 0) {
  //   std::shuffle(this->vertices.begin(), this->vertices.end(), std::mt19937());
  //   slope = (this->vertices[1][1] - this->vertices[0][1]) * (this->vertices[2][0] - this->vertices[1][0]) -
  //           (this->vertices[1][0] - this->vertices[0][0]) * (this->vertices[2][1] - this->vertices[1][1]);
  // }
  // std::sort(this->vertices.begin(), this->vertices.end(), [](const Vector &a, const Vector &b) { return a[0] < b[0];
  // }); if (this->vertices[1][1] > this->vertices[2][1]) {
  //   std::swap(this->vertices[1], this->vertices[2]);
  // }
  this->normal = calculateNormal();
}

const Texture &Triangle::getTexture() const {
  return this->texture;
}

Texture &Triangle::setTexture() {
  return this->texture;
}

Vector &Triangle::operator[](unsigned short i) {
  return this->vertices[i];
}

const Vector &Triangle::operator[](unsigned short i) const {
  return this->vertices[i];
}

Vector Triangle::calculateNormal() const {
  Vector v1 = this->vertices[1] - this->vertices[0];
  Vector v2 = this->vertices[2] - this->vertices[0];
  Vector result = (v1 * v2);
  result.normalize();
  return result;
}

const Vector &Triangle::getTriangleNormal() const {
  return this->normal;
}

float Triangle::area() const {
  return this->getTriangleNormal().length() / 2;
}
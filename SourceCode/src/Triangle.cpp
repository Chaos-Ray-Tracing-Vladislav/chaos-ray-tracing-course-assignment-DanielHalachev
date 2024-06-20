#include <tracer/Triangle.h>

#include <algorithm>
#include <array>
#include <istream>
#include <random>

#include "tracer/Utils.h"
#include "tracer/Vector.h"

Triangle::Triangle() : color(Color::randomColor()) {
  this->normal = getTriangleNormal();
};
Triangle::Triangle(std::array<Vector, 3> &vertices) : vertices(vertices), color(Color::randomColor()) {
  // I am not sure if this is the right way to do this
  // float slope = (this->vertices[1].x - this->vertices[0].x) * (this->vertices[2].y - this->vertices[0].y) -
  //               (this->vertices[1].y - this->vertices[0].y) * (this->vertices[2].x - this->vertices[0].x);
  // while (slope < 0) {
  //   std::shuffle(this->vertices.begin(), this->vertices.end(), std::mt19937());
  //   slope = (this->vertices[1].y - this->vertices[0].y) * (this->vertices[2].x - this->vertices[1].x) -
  //           (this->vertices[1].x - this->vertices[0].x) * (this->vertices[2].y - this->vertices[1].y);
  // }
  // std::sort(vertices.begin(), vertices.end(), [](const Vector &a, const Vector &b) { return a.x < b.x; });
  // if (this->vertices[1].y > this->vertices[2].y) {
  //   std::swap(this->vertices[1], this->vertices[2]);
  // }
  this->normal = getNormal();
}

Vector &Triangle::operator[](unsigned short i) {
  return this->vertices[i];
}

const Vector &Triangle::operator[](unsigned short i) const {
  return this->vertices[i];
}

std::istream &operator>>(std::istream &is, Triangle &triangle) {
  is >> triangle.vertices[0] >> triangle.vertices[1] >> triangle.vertices[2];
  return is;
}

Vector Triangle::getNormal() const {
  Vector v1 = this->vertices[1] - this->vertices[0];
  Vector v2 = this->vertices[2] - this->vertices[0];
  return v1 * v2;
}

Vector Triangle::getTriangleNormal() const {
  return this->normal;
}

float Triangle::area() const {
  return this->getTriangleNormal().length() / 2;
}
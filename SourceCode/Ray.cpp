#include "Ray.h"

#include <cmath>

Vector::Vector() : x(0), y(0), z(0){};

Vector::Vector(float x, float y, float z) : x(x), y(y), z(z){};

Vector Vector::operator-(const Vector& other) const {
  return {this->x - other.x, this->y - other.y, this->z - other.z};
}

Vector Vector::operator+(const Vector& other) const {
  return {this->x + other.x, this->y + other.y, this->z + other.z};
}

void Vector::normalize() {
  float length = this->length();
  this->x = this->x / this->length();
  this->y = this->y / this->length();
  this->z = this->z / this->length();
}

float Vector::length() const {
  return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
}

Ray::Ray() = default;

Ray::Ray(const Vector& origin, const Vector& direction) : origin(origin), direction(direction){};

Color Ray::generateColor() const {
  // return Color(static_cast<int>(std::abs(this->direction.x * 2)) % 255,
  //              static_cast<int>(std::abs(this->direction.y * 2)) % 255,
  //              static_cast<int>(std::abs(this->direction.z * 2)) % 255);
  return Color(static_cast<int>(std::abs(this->direction.x) * 255) % 255,
               static_cast<int>(std::abs(this->direction.y) * 255) % 255,
               static_cast<int>(std::abs(this->direction.z) * 255) % 255);
}
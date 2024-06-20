#include <tracer/Vector.h>

#include <cmath>
#include <istream>
#include <stdexcept>
#include <vector>

Vector::Vector() : x(0.0f), y(0.0f), z(0.0f){};

Vector::Vector(float x, float y, float z) : x(x), y(y), z(z){};

Vector::Vector(const std::vector<float>& values) {
  this->x = values[0];
  this->y = values[1];
  this->z = values[2];
}

const float& Vector::operator[](const unsigned short index) const {
  switch (index) {
    case 0:
      return this->x;
    case 1:
      return this->y;
    case 2:
      return this->z;
    default:
      throw std::out_of_range("Invalid range");
  }
}
float& Vector::operator[](const unsigned short index) {
  switch (index) {
    case 0:
      return this->x;
    case 1:
      return this->y;
    case 2:
      return this->z;
    default:
      throw std::out_of_range("Invalid range");
  }
}
Vector Vector::operator-(const Vector& other) const {
  return {this->x - other.x, this->y - other.y, this->z - other.z};
}

Vector Vector::operator+(const Vector& other) const {
  return {this->x + other.x, this->y + other.y, this->z + other.z};
}

Vector& Vector::operator+=(const Vector& other) {
  this->x += other.x;
  this->y += other.y;
  this->z += other.z;
  return *this;
}

float Vector::dot(const Vector& other) const {
  return this->x * other.x + this->y * other.y + this->z * other.z;
}

Vector Vector::operator*(const Vector& other) const {
  return Vector(this->y * other.z - this->z * other.y,  // x
                this->z * other.x - this->x * other.z,  // y
                this->x * other.y - this->y * other.x   // x
  );
}

Vector Vector::operator*(float scalar) const {
  return Vector(this->x * scalar, this->y * scalar, this->z * scalar);
}

Vector operator*(float lhs, const Vector& rhs) {
  return Vector(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
}

std::ostream& operator<<(std::ostream& os, const Vector& vector) {
  os << "[" << vector.x << "," << vector.y << "," << vector.z << "]";
  return os;
}

std::istream& operator>>(std::istream& is, Vector& vector) {
  char leftBracket = '[';
  char rightBracket = ']';
  char delim = ',';
  is >> leftBracket >> vector.x >> delim >> vector.y >> delim >> vector.z >> rightBracket;
  return is;
}

void Vector::normalize() {
  float length = this->length();
  length = 1 / length;
  this->x = this->x * length;
  this->y = this->y * length;
  this->z = this->z * length;
}

float Vector::length() const {
  return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
}
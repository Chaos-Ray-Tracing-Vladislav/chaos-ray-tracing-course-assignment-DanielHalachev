#pragma once
#include <ostream>
struct Vector {
  float x;
  float y;
  float z;
  Vector();
  Vector(float x, float y, float z);
  Vector operator-(const Vector &other) const;
  Vector operator+(const Vector &other) const;
  Vector operator*(const Vector &other) const;
  Vector operator*(float scalar) const;
  friend Vector operator*(float lhs, const Vector &rhs);
  friend std::ostream &operator<<(std::ostream &os, const Vector &vector);
  void normalize();
  float length() const;
};

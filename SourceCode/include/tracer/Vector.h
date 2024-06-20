#pragma once
#include <ostream>
#include <vector>
struct Vector {
  float x;
  float y;
  float z;
  Vector();
  Vector(float x, float y, float z);
  explicit Vector(const std::vector<float> &values);
  const float &operator[](const unsigned short index) const;
  float &operator[](const unsigned short index);
  Vector operator-(const Vector &other) const;
  Vector operator+(const Vector &other) const;
  Vector &operator+=(const Vector &other);
  float dot(const Vector &other) const;
  Vector operator*(const Vector &other) const;
  Vector operator*(float scalar) const;
  friend Vector operator*(float lhs, const Vector &rhs);
  friend std::ostream &operator<<(std::ostream &os, const Vector &vector);
  friend std::istream &operator>>(std::istream &is, Vector &vector);
  void normalize();
  float length() const;
};

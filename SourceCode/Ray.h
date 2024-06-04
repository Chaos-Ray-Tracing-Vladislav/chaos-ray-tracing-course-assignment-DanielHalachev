#ifndef RAY_H
#define RAY_H
#include <ostream>
struct Vector {
  float x;
  float y;
  float z;
  Vector();
  Vector(float x, float y, float z);
  Vector operator-(const Vector &other) const;
  Vector operator+(const Vector &other) const;
  void normalize();
  float length() const;
};

struct Color {
  unsigned short red;
  unsigned short green;
  unsigned short blue;
  Color(unsigned short red, unsigned short green, unsigned short blue) : red(red), green(green), blue(blue){};
  friend std::ostream &operator<<(std::ostream &os, const struct Color &color) {
    os << color.red << " " << color.green << " " << color.blue;
    return os;
  }
};

struct Ray {
  Vector origin;
  Vector direction;

  Ray();
  Ray(const Vector &origin, const Vector &direction);
  Color generateColor() const;
};

#endif  // RAY_H
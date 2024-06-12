#include <tracer/Ray.h>

#include <cmath>

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
#pragma once

#include <optional>

#include "Vector.h"
#include "tracer/Triangle.h"

class Ray {
 public:
  Vector origin;
  Vector direction;

  Ray();
  Ray(const Vector &origin, const Vector &direction);
  // Ray(const Ray &other) = default;
  // Ray &operator=(const Ray &other) = default;
  // Ray(Ray &&other) = default;
  // Ray &operator=(Ray &&other) = default;

  // TODO (maybe move to Triangle.h)
  std::optional<Vector> intersectWithTriangle(const Triangle &triangle, bool isPrimaryRay = true) const;
};
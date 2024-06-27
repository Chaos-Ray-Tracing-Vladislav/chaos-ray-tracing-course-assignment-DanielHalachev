#pragma once

#include <optional>

#include "Vector.h"
#include "tracer/Triangle.h"

enum RayType { Primary, Shadow };

template <RayType T = Primary>
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
  std::optional<Vector> intersectWithTriangle(const Triangle &triangle) const;
};

template <RayType T>
Ray<T>::Ray() = default;

template <RayType T>
Ray<T>::Ray(const Vector &origin, const Vector &direction) : origin(origin), direction(direction){};

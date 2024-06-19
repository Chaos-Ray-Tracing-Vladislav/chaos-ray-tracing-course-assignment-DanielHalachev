#pragma once

#include <optional>

#include "Utils.h"
#include "Vector.h"
#include "tracer/Triangle.h"

struct Ray {
  constexpr static const float FLOAT_EPSILON = 1e-8;
  Vector origin;
  Vector direction;

  Ray();
  Ray(const Vector &origin, const Vector &direction);
  std::optional<Vector> intersectWithTriangle(const Triangle &triangle) const;
  Color generateColor() const;
};
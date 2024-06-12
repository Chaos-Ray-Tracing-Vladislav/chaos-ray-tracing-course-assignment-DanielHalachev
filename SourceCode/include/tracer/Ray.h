#pragma once

#include "Utils.h"
#include "Vector.h"
struct Ray {
  Vector origin;
  Vector direction;

  Ray();
  Ray(const Vector &origin, const Vector &direction);
  Color generateColor() const;
};
#pragma once

#include <optional>

#include "Vector.h"
#include "tracer/Triangle.h"

class RayBase {
 public:
  Vector origin;
  Vector direction;

  RayBase();
  RayBase(const Vector &origin, const Vector &direction);
  // Ray(const Ray &other) = default;
  // Ray &operator=(const Ray &other) = default;
  // Ray(Ray &&other) = default;
  // Ray &operator=(Ray &&other) = default;
  virtual ~RayBase() = default;

  // TODO (maybe move to Triangle.h)
  virtual std::optional<Vector> intersectWithTriangle(const Triangle &triangle) const = 0;
};

class Ray : public RayBase {
 public:
  using RayBase::RayBase;
  virtual std::optional<Vector> intersectWithTriangle(const Triangle &triangle) const;
  ~Ray() = default;
};

class ShadowRay : public RayBase {
 public:
  using RayBase::RayBase;
  virtual std::optional<Vector> intersectWithTriangle(const Triangle &triangle) const;
  ~ShadowRay() = default;
};

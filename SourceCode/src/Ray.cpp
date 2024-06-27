#include <tracer/Ray.h>

// #include <limits>
#include <cmath>
#include <limits>
#include <optional>

#include "tracer/Triangle.h"
#include "tracer/Vector.h"



#if 0

std::optional<Vector> Ray::intersectWithTriangle(const Triangle& triangle, const Vector& cameraPosition) const {
  Vector triangleNormal = triangle.getTriangleNormal();
  float normalDotRayDirection = this->direction.dot(triangleNormal);

  //   if (normalDotRayDirection >= 0) {
  //     return {};
  //   }

  // if N . R ~= 0, the ray is parallel to the plane - no intersection or too far away
  // if (std::fabs(normalDotRayDirection) < std::numeric_limits<float>::epsilon()) {
  //   return {};
  // }

  float distanceToPlane = (triangle[0] - cameraPosition).dot(triangleNormal);

  float t = distanceToPlane / normalDotRayDirection;

  Vector intersectionPoint = this->origin + t * this->direction;

  if (!triangle.pointIsInTriangle(intersectionPoint)) {
    return {};
  }

  return intersectionPoint;
}

std::optional<Vector> ShadowRay::intersectWithTriangle(const Triangle& triangle, const Vector& cameraPosition) const {
  Vector triangleNormal = triangle.getTriangleNormal();
  float normalDotRayDirection = this->direction.dot(triangleNormal);

  if (normalDotRayDirection == 0) {
    return {};
  }

  // if N . R ~= 0, the ray is parallel to the plane - no intersection or too far away
  // if (std::fabs(normalDotRayDirection) < std::numeric_limits<float>::epsilon()) {
  //   return {};
  // }

  float distanceToPlane = (triangle[0] - cameraPosition).dot(triangleNormal);

  float t = distanceToPlane / normalDotRayDirection;

  Vector intersectionPoint = this->origin + t * this->direction;

  if (!triangle.pointIsInTriangle(intersectionPoint)) {
    return {};
  }

  return intersectionPoint;
}

#else
template <>
std::optional<Vector> Ray<Primary>::intersectWithTriangle(const Triangle& triangle) const {
  Vector triangleNormal = triangle.getTriangleNormal();
  float normalDotRayDirection = this->direction.dot(triangleNormal);

  if (normalDotRayDirection >= 0) {
    return {};
  }

  // if N . R ~= 0, the ray is parallel to the plane - no intersection or too far away
  //   if (std::fabs(normalDotRayDirection) < std::numeric_limits<float>::epsilon()) {
  //     return {};
  //   }

  float distanceToPlane = -(triangle[0]).dot(triangleNormal);

  float t = -(triangleNormal.dot(this->origin) + distanceToPlane) / normalDotRayDirection;
  if (t < 0) {
    return {};
  }
  Vector intersectionPoint = this->origin + this->direction * t;

  if (!triangle.pointIsInTriangle(intersectionPoint)) {
    return {};
  }

  return intersectionPoint;
}

template <>
std::optional<Vector> Ray<Shadow>::intersectWithTriangle(const Triangle& triangle) const {
  Vector triangleNormal = triangle.getTriangleNormal();
  float normalDotRayDirection = this->direction.dot(triangleNormal);

  // if N . R ~= 0, the ray is parallel to the plane - no intersection or too far away
  // if (std::fabs(normalDotRayDirection) < std::numeric_limits<float>::epsilon()) {
  //   return {};
  // }

  float distanceToPlane = -(triangle[0]).dot(triangleNormal);

  float t = -(triangleNormal.dot(this->origin) + distanceToPlane) / normalDotRayDirection;
  if (t < 0) {
    return {};
  }
  Vector intersectionPoint = this->origin + this->direction * t;

  if (!triangle.pointIsInTriangle(intersectionPoint)) {
    return {};
  }

  return intersectionPoint;
}
#endif
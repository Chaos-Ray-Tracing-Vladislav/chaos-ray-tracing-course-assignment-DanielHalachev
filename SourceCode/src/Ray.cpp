#include <tracer/Ray.h>

// #include <limits>
#include <optional>

#include "tracer/Triangle.h"
#include "tracer/Vector.h"

Ray::Ray() = default;

Ray::Ray(const Vector& origin, const Vector& direction) : origin(origin), direction(direction){};

std::optional<Vector> Ray::intersectWithTriangle(const Triangle& triangle) const {
  Vector triangleNormal = triangle.getTriangleNormal();
  float normalDotRayDirection = this->direction.dot(triangleNormal);

  if (normalDotRayDirection >= 0) {
    return {};
  }

  // if N . R ~= 0, the ray is parallel to the plane - no intersection or too far away
  // if (std::fabs(normalDotRayDirection) < std::numeric_limits<float>::epsilon()) {
  //   return {};
  // }

  float distanceToPlane = (triangle[0] - this->origin).dot(triangleNormal);

  float t = distanceToPlane / normalDotRayDirection;

  Vector intersectionPoint = this->origin + t * this->direction;

  Vector e0 = triangle[1] - triangle[0];
  Vector c0 = intersectionPoint - triangle[0];
  if (triangleNormal.dot(e0 * c0) < 0) {
    return {};
  }

  Vector e1 = triangle[2] - triangle[1];
  Vector c1 = intersectionPoint - triangle[1];
  if (triangleNormal.dot(e1 * c1) < 0) {
    return {};
  }

  Vector e2 = triangle[0] - triangle[2];
  Vector c2 = intersectionPoint - triangle[2];
  if (triangleNormal.dot(e2 * c2) < 0) {
    return {};
  }

  return intersectionPoint;
}

// std::optional<Vector> Ray::intersectWithTriangle(const Triangle& triangle) const {
//   Vector triangleNormal = triangle.getTriangleNormal();
//   float normalDotRayDirection = this->direction.dot(triangleNormal);

//   if (normalDotRayDirection >= 0) {
//     return {};
//   }

//   // if N . R ~= 0, the ray is parallel to the plane - no intersection or too far away
//   // if (std::fabs(normalDotRayDirection) < std::numeric_limits<float>::epsilon()) {
//   //   return {};
//   // }

//   float distanceToPlane = -(triangle[0] - this->origin).dot(triangleNormal);

//   float t = -(triangleNormal.dot(this->origin) + distanceToPlane) / normalDotRayDirection;
//   if (t < 0) {
//     return {};
//   }
//   Vector intersectionPoint = this->origin + this->direction * t;

//   Vector e0 = triangle[1] - triangle[0];
//   Vector c0 = intersectionPoint - triangle[0];
//   if (triangleNormal.dot(e0 * c0) < 0) {
//     return {};
//   }

//   Vector e1 = triangle[2] - triangle[1];
//   Vector c1 = intersectionPoint - triangle[1];
//   if (triangleNormal.dot(e1 * c1) < 0) {
//     return {};
//   }

//   Vector e2 = triangle[0] - triangle[2];
//   Vector c2 = intersectionPoint - triangle[2];
//   if (triangleNormal.dot(e2 * c2) < 0) {
//     return {};
//   }

//   return intersectionPoint;
// }
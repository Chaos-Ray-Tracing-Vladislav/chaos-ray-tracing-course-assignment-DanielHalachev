#pragma once
#include <cstddef>
#include <string>
#include <vector>

#include "Ray.h"
#include "SceneSettings.h"
#include "tracer/Camera.h"
#include "tracer/Vector.h"

typedef Vector ColorVector;
#define MAX_DEPTH 5

class RayTracer {
 private:
  struct IntersectionInformation {
    Vector intersectionPoint;
    size_t objectIndex;
    size_t triangleIndex;
  };

  bool rayUpdateRequired;
  bool renderRequired;
  Scene scene;
  std::vector<std::vector<Ray>> pixelRays;
  std::vector<std::vector<Color>> colorBuffer;
  void updateRays();
  Color shootRay(const Ray &ray, const unsigned int depth = 0) const;
  Color shade(const Ray &ray) const;
  std::optional<RayTracer::IntersectionInformation> trace(const Ray &ray) const;
  bool hasIntersection(const Ray &ray) const;

 public:
  explicit RayTracer(const std::string &pathToScene);
  const Camera getCamera() const;
  Camera &setCamera();
  void render();
  void writePPM(const std::string &pathToImage);
};
#pragma once
#include <string>
#include <vector>

#include "Ray.h"
#include "SceneSettings.h"
#include "tracer/Camera.h"

class RayTracer {
 private:
  bool rayUpdateRequired;
  Scene scene;
  std::vector<std::vector<Ray>> pixelRays;
  void updateRays();

 public:
  explicit RayTracer(const std::string &pathToScene);
  const Camera &getCamera() const;
  Camera &setCamera();
  void generatePPM(const std::string &pathToImage);
};
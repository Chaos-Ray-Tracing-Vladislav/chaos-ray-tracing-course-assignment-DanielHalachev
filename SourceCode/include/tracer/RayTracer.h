#pragma once
#include <string>
#include <vector>

#include "Image.h"
#include "Ray.h"
#include "SceneParser.h"
#include "Triangle.h"

class RayTracer {
 private:
  Image image;
  SceneParser sceneParser;
  std::vector<Triangle> sceneTriangles;
  std::vector<std::vector<Ray>> pixelRays;
  void generateRays();

 public:
  explicit RayTracer(const Image &image, const std::string &pathToScene);
  void generatePPM(const std::string &pathToImage) const;
};
#pragma once
#include <string>
#include <vector>

#include "Image.h"
#include "Ray.h"
#include "SceneParser.h"
#include "Triangle.h"
#include "tracer/Camera.h"

class RayTracer {
 private:
  bool rayUpdateRequired;
  Image image;
  Camera camera;
  SceneParser sceneParser;
  std::vector<Triangle> sceneTriangles;
  std::vector<std::vector<Ray>> pixelRays;
  void updateRays();

 public:
  RayTracer(const Image &image, const Camera &camera, const std::string &pathToScene);
  const Image &getImage() const;
  Image &setImage();
  const Camera &getCamera() const;
  Camera &setCamera();
  void updateScene(const std::string &pathToNewScene);
  void generatePPM(const std::string &pathToImage);
};
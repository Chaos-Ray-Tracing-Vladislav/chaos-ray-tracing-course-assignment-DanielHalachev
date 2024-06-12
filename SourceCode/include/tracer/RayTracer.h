#pragma once
#include <string>
#include <vector>

#include "Image.h"
#include "Ray.h"

class RayTracer {
 private:
  Image image;
  std::vector<std::vector<Ray>> pixelRays;
  void generateRays();

 public:
  explicit RayTracer(const Image &image);
  void generatePPM(const std::string &pathToImage) const;
};
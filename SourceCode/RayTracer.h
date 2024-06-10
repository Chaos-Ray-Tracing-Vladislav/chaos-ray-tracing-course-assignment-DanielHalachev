#ifndef RAY_TRACER_H
#define RAY_TRACER_H
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
  RayTracer(const Image &image);
  void generatePPM(const std::string &pathToImage) const;
};
#endif  // RAY_TRACER_H
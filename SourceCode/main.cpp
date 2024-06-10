#include <string>

#include "RayTracer.h"
int main() {
  std::vector<Image> images = {{3840, 2160}, {1600, 900}, {1920, 1080}, {400, 300}, {1920, 1920}};
  for (auto &image : images) {
    RayTracer rayTracer(image);
    rayTracer.generatePPM("/home/daniel/tracer" + std::to_string(image.width) + "x" + std::to_string(image.height) +
                          ".ppm");
  }
  return 0;
}
#include <tracer/Triangle.h>

#include <string>

#include "tracer/RayTracer.h"

int main() {
  Image image{1920, 1080};
  RayTracer rayTracer(image, "/home/daniel/scene4.txt");
  rayTracer.generatePPM("/home/daniel/result4.ppm");

  return 0;
}
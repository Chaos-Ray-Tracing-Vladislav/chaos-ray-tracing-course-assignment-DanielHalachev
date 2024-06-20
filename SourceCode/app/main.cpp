#include <string>

#include "tracer/RayTracer.h"

int main() {
  for (short i = 0; i < 5; i++) {
    RayTracer tracer("/home/daniel/scene" + std::to_string(i) + ".crtscene");
    tracer.generatePPM("/home/daniel/result" + std::to_string(i) + ".ppm");
  }
  return 0;
}
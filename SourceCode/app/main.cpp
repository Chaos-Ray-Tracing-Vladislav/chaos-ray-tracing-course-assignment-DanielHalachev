#include <cmath>
#include <string>

#include "tracer/Camera.h"
#include "tracer/RayTracer.h"

int main() {
  Image image{1920, 1080};
  Camera camera({2, 2, 2});
  // Task 2
  RayTracer rayTracer(image, camera, "/home/daniel/HW06/scene1.txt");
  rayTracer.generatePPM("/home/daniel/HW06/2.ppm");
  // Task 3 & 4
  rayTracer.setCamera().setPosition() = {0, 0, 0};
  rayTracer.generatePPM("/home/daniel/HW06/3+4-0.ppm");
  rayTracer.setCamera().truck({1, 1, -1}).pan(15);
  rayTracer.generatePPM("/home/daniel/HW06/3+4-1.ppm");
  // Task 5
  camera = Camera({0, 0, 0});
  rayTracer = RayTracer(image, camera, "/home/daniel/HW06/scene1.txt");
  const short FPS = 24;
  const short SECONDS = 2;
  const float DEG_CHANGE = 90.0f / (FPS * SECONDS);
  float degrees = -45;
  for (float t = 0; t <= FPS * SECONDS; t++) {
    float radians = degrees * (22 / (7 * 180.0f));
    rayTracer.setCamera().setPosition() = (Vector{std::sinf(radians) * 3, 0, std::cosf(radians) * 3 - 2.75f});
    rayTracer.setCamera().pan(-DEG_CHANGE * (22 / (7 * 180.0f)));
    rayTracer.generatePPM("/home/daniel/HW06/Movie/" + std::to_string(static_cast<int>(t)) + ".ppm");
    degrees += DEG_CHANGE;
  }
  return 0;
}
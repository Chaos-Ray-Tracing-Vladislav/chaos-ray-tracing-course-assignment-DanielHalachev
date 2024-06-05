#include "CircleGenerator.h"
#include "RectangleGenerator.h"
int main() {
  RectangleGenerator rectangleGenerator(1920, 1080);
  rectangleGenerator.generatePPM("/home/daniel/rectangles.ppm");

  CircleGenerator circleGenerator({1920 / 2, 1080 / 2}, 1080 / 4, 1920, 1080);
  circleGenerator.generatePPM("/home/daniel/circle.ppm");
  return 0;
}
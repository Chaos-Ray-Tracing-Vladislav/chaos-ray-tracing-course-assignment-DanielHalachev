#include <tracer/RayTracer.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <optional>
#include <vector>

#include "tracer/Utils.h"
#include "tracer/Vector.h"

RayTracer::RayTracer(const Image &image, const std::string &pathToScene) : image(image) {
  this->pixelRays.resize(this->image.height);
  for (auto &row : this->pixelRays) {
    row.resize(this->image.width);
  }
  this->generateRays();
  this->sceneTriangles = this->sceneParser.parseScene(pathToScene);
};

void RayTracer::generateRays() {
  for (unsigned int pixelRow = 0; pixelRow < image.height; pixelRow++) {
    for (unsigned int pixelCol = 0; pixelCol < image.width; pixelCol++) {
      float x = pixelCol + 0.5;
      float y = pixelRow + 0.5;

      x = x / image.width;
      y = y / image.height;

      x = (2.0 * x) - 1.0;
      y = 1 - (2.0 * y);

      x = x * (static_cast<float>(image.width) / static_cast<float>(image.height));

      Vector direction(x, y, -1.0);
      direction.normalize();
      this->pixelRays[pixelRow][pixelCol] = Ray(Vector(0, 0, 0), direction);
    }
  }
}

void RayTracer::generatePPM(const std::string &pathToImage) const {
  std::ofstream outputStream(pathToImage);
  outputStream << "P3"
               << "\n"
               << this->image.width << " " << this->image.height << "\n"
               << 255 << "\n";
  for (unsigned int pixelRow = 0; pixelRow < image.height; pixelRow++) {
    for (unsigned int pixelCol = 0; pixelCol < image.width; pixelCol++) {
      std::vector<Vector> points;
      for (auto &triangle : this->sceneTriangles) {
        std::optional<Vector> intersectionPoint = this->pixelRays[pixelRow][pixelCol].intersectWithTriangle(triangle);
        if (intersectionPoint.has_value()) {
          points.push_back(intersectionPoint.value());
        }
      }
      if (points.empty()) {
        outputStream << Color::black << "\t";
      } else {
        auto min = std::min_element(points.begin(), points.end(), [](const Vector &a, const Vector &b) {
          if (a.length() < b.length()) {
            return true;
          }
          return false;
        });
        outputStream << Color::white << "\t";
      }
    }
    outputStream << "\n";
  }
}
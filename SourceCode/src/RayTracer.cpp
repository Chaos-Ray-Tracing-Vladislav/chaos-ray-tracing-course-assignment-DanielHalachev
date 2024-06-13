
#include "tracer/RayTracer.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <optional>
#include <vector>

#include "tracer/Utils.h"
#include "tracer/Vector.h"

RayTracer::RayTracer(const Image &image, const Camera &camera, const std::string &pathToScene)
    : rayUpdateRequired(true), image{image}, camera{camera} {
  this->updateScene(pathToScene);
};

const Image &RayTracer::getImage() const {
  return this->image;
}

Image &RayTracer::setImage() {
  this->rayUpdateRequired = true;
  return this->image;
}

const Camera &RayTracer::getCamera() const {
  return this->camera;
}

Camera &RayTracer::setCamera() {
  this->rayUpdateRequired = true;
  return this->camera;
}

void RayTracer::updateScene(const std::string &pathToNewScene) {
  this->sceneTriangles = this->sceneParser.parseScene(pathToNewScene);
}

void RayTracer::updateRays() {
  this->pixelRays.resize(this->image.height);
  for (auto &row : this->pixelRays) {
    row.resize(this->image.width);
  }
  for (unsigned int pixelRow = 0; pixelRow < this->image.height; pixelRow++) {
    for (unsigned int pixelCol = 0; pixelCol < this->image.width; pixelCol++) {
      float x = static_cast<float>(pixelCol) + 0.5f;
      float y = static_cast<float>(pixelRow) + 0.5f;

      x = x / static_cast<float>(image.width);
      y = y / static_cast<float>(image.height);

      x = (2.0f * x) - 1.0f;
      y = 1.0f - (2.0f * y);

      x = x * (static_cast<float>(image.width) / static_cast<float>(image.height));

      Vector direction(x, y, -1.0);
      direction = direction * this->camera.getRotationMatrix();
      direction.normalize();
      this->pixelRays[pixelRow][pixelCol] = Ray(this->camera.getPosition(), direction);
    }
  }
  this->rayUpdateRequired = false;
}

void RayTracer::generatePPM(const std::string &pathToImage) {
  if (this->rayUpdateRequired == true) {
    this->updateRays();
  }
  std::ofstream outputStream(pathToImage);
  outputStream << "P3"
               << "\n"
               << this->image.width << " " << this->image.height << "\n"
               << 255 << "\n";  // WTF? Doesn't work otherwise
  for (unsigned int pixelRow = 0; pixelRow < image.height; pixelRow++) {
    for (unsigned int pixelCol = 0; pixelCol < image.width; pixelCol++) {
      float minDistance = INFINITY;
      std::optional<Vector> intersectionPoint = {};
      for (auto &triangle : this->sceneTriangles) {
        std::optional<Vector> tempIntersectionPoint =
            this->pixelRays[pixelRow][pixelCol].intersectWithTriangle(triangle);
        if (tempIntersectionPoint.has_value()) {
          float distance = tempIntersectionPoint.value().length();
          if (distance < minDistance) {
            minDistance = distance;
            intersectionPoint = tempIntersectionPoint.value();
          }
        }
      }
      if (intersectionPoint.has_value()) {
        outputStream << Color::white << "\t";
      } else {
        outputStream << Color::black << "\t";
      }
    }
    outputStream << "\n";
  }
}
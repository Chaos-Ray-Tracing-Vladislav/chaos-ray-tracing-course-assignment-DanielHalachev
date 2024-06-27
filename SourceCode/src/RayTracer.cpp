
#include "tracer/RayTracer.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <optional>
#include <vector>

#include "tracer/SceneParser.h"
#include "tracer/Triangle.h"
#include "tracer/Utils.h"
#include "tracer/Vector.h"

RayTracer::RayTracer(const std::string &pathToScene) : rayUpdateRequired(true) {
  this->scene = SceneParser::parseScene(pathToScene);
};

const Camera &RayTracer::getCamera() const {
  return this->scene.getCamera();
}

Camera &RayTracer::setCamera() {
  this->rayUpdateRequired = true;
  return this->scene.setCamera();
}

void RayTracer::updateRays() {
  this->pixelRays.resize(this->scene.sceneSettings.image.height);
  for (auto &row : this->pixelRays) {
    row.resize(this->scene.sceneSettings.image.width);
  }
  for (unsigned int pixelRow = 0; pixelRow < this->scene.sceneSettings.image.height; pixelRow++) {
    for (unsigned int pixelCol = 0; pixelCol < this->scene.sceneSettings.image.width; pixelCol++) {
      float x = static_cast<float>(pixelCol) + 0.5f;
      float y = static_cast<float>(pixelRow) + 0.5f;

      x = x / static_cast<float>(this->scene.sceneSettings.image.width);
      y = y / static_cast<float>(this->scene.sceneSettings.image.height);

      x = (2.0f * x) - 1.0f;
      y = 1.0f - (2.0f * y);

      x = x * (static_cast<float>(this->scene.sceneSettings.image.width) /
               static_cast<float>(this->scene.sceneSettings.image.height));

      Vector direction(x, y, -1.0);
      direction = direction * this->scene.getCamera().getRotationMatrix();
      direction.normalize();
      this->pixelRays[pixelRow][pixelCol] = Ray(this->scene.getCamera().getPosition(), direction);
    }
  }
}

void RayTracer::generatePPM(const std::string &pathToImage) {
  if (this->rayUpdateRequired == true) {
    this->updateRays();
  }
  std::ofstream outputStream(pathToImage);
  outputStream << "P3"
               << "\n"
               << this->scene.sceneSettings.image.width << " " << this->scene.sceneSettings.image.height << "\n"
               << 255 << "\n";
  std::vector<Triangle> sceneTriangles;
  for (auto &mesh : this->scene.objects) {
    sceneTriangles.insert(sceneTriangles.end(), mesh.triangles.begin(), mesh.triangles.end());
  }
  for (unsigned int pixelRow = 0; pixelRow < this->scene.sceneSettings.image.height; pixelRow++) {
    for (unsigned int pixelCol = 0; pixelCol < this->scene.sceneSettings.image.width; pixelCol++) {
      float minDistance = INFINITY;
      std::optional<Vector> intersectionPoint = {};
      std::optional<Triangle> intersectedTriangle = {};
      for (auto &triangle : sceneTriangles) {
        std::optional<Vector> tempIntersectionPoint =
            this->pixelRays[pixelRow][pixelCol].intersectWithTriangle(triangle);
        if (tempIntersectionPoint.has_value()) {
          float distance = tempIntersectionPoint.value().length();
          if (distance < minDistance) {
            minDistance = distance;
            intersectionPoint = tempIntersectionPoint.value();
            intersectedTriangle = triangle;
          }
        }
      }
      // TODO (decouple from ray tracing logic)
      if (intersectionPoint.has_value()) {
        outputStream << intersectedTriangle->color << "\t";
      } else {
        outputStream << this->scene.sceneSettings.sceneBackgroundColor << "\t";
      }
    }
    outputStream << "\n";
  }
}
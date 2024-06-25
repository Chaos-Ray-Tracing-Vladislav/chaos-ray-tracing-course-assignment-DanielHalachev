
#include "tracer/RayTracer.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <limits>
#include <optional>
#include <vector>

#include "tracer/Camera.h"
#include "tracer/Ray.h"
#include "tracer/SceneParser.h"
#include "tracer/SceneSettings.h"
#include "tracer/Triangle.h"
#include "tracer/Utils.h"
#include "tracer/Vector.h"

const float PI = (22.0f / 7.0f);

void printProgress(double percentage) {
  const char *progressBarString = "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||";
  const int progressBarWidth = 60;
  int val = static_cast<int>(percentage * 100);
  int leftPadding = static_cast<int>(percentage * progressBarWidth);
  int rightPadding = progressBarWidth - leftPadding;
  printf("\r%3d%% [%.*s%*s]", val, leftPadding, progressBarString, rightPadding, "");
  fflush(stdout);
}

RayTracer::RayTracer(const std::string &pathToScene) : rayUpdateRequired(true), renderRequired(true) {
  this->scene = SceneParser::parseScene(pathToScene);
};

const Camera &RayTracer::getCamera() const {
  return this->scene.camera;
}

Camera &RayTracer::setCamera() {
  this->rayUpdateRequired = true;
  this->renderRequired = true;
  return this->scene.camera;
}

void RayTracer::updateRays() {
  this->pixelRays.resize(this->scene.sceneSettings.image.height);
  for (auto &row : this->pixelRays) {
    row.resize(this->scene.sceneSettings.image.width);
  }
  this->colorBuffer.resize(this->scene.sceneSettings.image.height);
  for (auto &row : this->colorBuffer) {
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
      direction = direction * this->scene.camera.getRotationMatrix();
      direction.normalize();
      this->pixelRays[pixelRow][pixelCol] = Ray(this->scene.camera.getPosition(), direction);
    }
  }
}

void RayTracer::render() {
  auto startTime = std::chrono::high_resolution_clock::now();
  if (this->rayUpdateRequired == true) {
    this->updateRays();
  }
  for (unsigned int pixelRow = 0; pixelRow < this->scene.sceneSettings.image.height; pixelRow++) {
    for (unsigned int pixelCol = 0; pixelCol < this->scene.sceneSettings.image.width; pixelCol++) {
      this->colorBuffer[pixelRow][pixelCol] = this->shootRay(this->pixelRays[pixelRow][pixelCol]);
    }
    printProgress(static_cast<float>(pixelRow) / static_cast<float>(this->scene.sceneSettings.image.height));
  }
  std::cout << std::endl;
  this->renderRequired = false;

#if defined(MEASURE_TIME) && MEASURE_TIME
  auto endTime = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = endTime - startTime;
  std::cout << duration.count() << "s\n";
#endif  // MEASURE_TIME
}

Color RayTracer::shootRay(const Ray &ray, const unsigned int depth) const {
  if (depth > MAX_DEPTH) {
    return this->scene.sceneSettings.sceneBackgroundColor;
  }
  std::optional<IntersectionInformation> intersectionInformation = trace(ray);
  if (intersectionInformation.has_value()) {
    const Vector &intersectionPoint = intersectionInformation->intersectionPoint;
    const Mesh &mesh = *intersectionInformation->object;
    const Triangle &triangle = *intersectionInformation->triangle;

    Vector finalColor(0, 0, 0);

    for (auto &light : this->scene.lights) {
      Vector lightDirection = light.position - intersectionPoint;
      float sphereRadius = lightDirection.length();
      float sphereArea = 4 * sphereRadius * sphereRadius * PI;
      lightDirection.normalize();
      float angle = std::max(0.0f, lightDirection.dot(triangle.getTriangleNormal()));

      Ray shadowRay(intersectionPoint + triangle.getTriangleNormal() * SHADOW_BIAS, lightDirection);
      bool shadowRayIntersection = hasIntersection(shadowRay);

      if (!shadowRayIntersection) {
        float lightContribution = (static_cast<float>(light.intentsity) / sphereArea * angle);
        finalColor += lightContribution * triangle.getTexture().albedo;
      }
    }
    return Color(finalColor);
  }
  return this->scene.sceneSettings.sceneBackgroundColor;
}

std::optional<RayTracer::IntersectionInformation> RayTracer::trace(const Ray &ray, bool isPrimary) const {
  float minDistance = std::numeric_limits<float>::infinity();
  std::optional<Vector> intersectionPoint = {};
  const Mesh *intersectedObject = nullptr;
  const Triangle *intersectedTriangle = nullptr;

  for (auto &object : this->scene.objects) {
    for (auto &triangle : object.triangles) {
      std::optional<Vector> tempIntersectionPoint = ray.intersectWithTriangle(triangle, isPrimary);
      if (tempIntersectionPoint.has_value()) {
        float distance = (tempIntersectionPoint.value() - ray.origin).length();
        if (distance < minDistance) {
          minDistance = distance;
          intersectionPoint = tempIntersectionPoint.value();
          intersectedObject = &object;
          intersectedTriangle = &triangle;
        }
      }
    }
  }
  if (intersectionPoint.has_value()) {
    return IntersectionInformation{intersectionPoint.value(), intersectedObject, intersectedTriangle};
  }
  return {};
}

bool RayTracer::hasIntersection(const Ray &ray) const {
  for (auto &object : this->scene.objects) {
    for (auto &triangle : object.triangles) {
      if (ray.intersectWithTriangle(triangle, false).has_value()) {
        return true;
      }
    }
  }
  return false;
}

void RayTracer::writePPM(const std::string &pathToImage) {
  if (this->renderRequired == true) {
    this->render();
  }
  std::ofstream outputStream(pathToImage);
  outputStream << "P3"
               << "\n"
               << this->scene.sceneSettings.image.width << " " << this->scene.sceneSettings.image.height << "\n"
               << 255 << "\n";
  for (unsigned int pixelRow = 0; pixelRow < this->scene.sceneSettings.image.height; pixelRow++) {
    for (unsigned int pixelCol = 0; pixelCol < this->scene.sceneSettings.image.width; pixelCol++) {
      outputStream << PPMColor(this->colorBuffer[pixelRow][pixelCol]) << "\t";
    }
    outputStream << "\n";
  }
}

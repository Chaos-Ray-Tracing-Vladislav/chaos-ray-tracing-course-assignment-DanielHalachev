
#include "tracer/RayTracer.h"

#include <cmath>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <optional>
#include <vector>

#include "tracer/Camera.h"
#include "tracer/Ray.h"
#include "tracer/SceneParser.h"
#include "tracer/SceneSettings.h"
#include "tracer/Triangle.h"
#include "tracer/Utils.h"
#include "tracer/Vector.h"

RayTracer::RayTracer(const std::string &pathToScene) : rayUpdateRequired(true), renderRequired(true) {
  this->scene = SceneParser::parseScene(pathToScene);
};

const Camera RayTracer::getCamera() const {
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
  if (this->rayUpdateRequired == true) {
    this->updateRays();
  }
  for (unsigned int pixelRow = 0; pixelRow < this->scene.sceneSettings.image.height; pixelRow++) {
    for (unsigned int pixelCol = 0; pixelCol < this->scene.sceneSettings.image.width; pixelCol++) {
      this->colorBuffer[pixelRow][pixelCol] = this->shootRay(this->pixelRays[pixelRow][pixelCol]);
    }
  }
}

Color RayTracer::shootRay(const Ray &ray, const unsigned int depth) const {
  if (depth > MAX_DEPTH) {
    return this->scene.sceneSettings.sceneBackgroundColor;
  }
  std::optional<IntersectionInformation> intersectionInformation = trace(ray);
  if (intersectionInformation.has_value()) {
    Vector intersectionPoint = intersectionInformation->intersectionPoint;
    Mesh mesh = this->scene.objects[intersectionInformation->objectIndex];
    Triangle triangle = mesh.triangles[intersectionInformation->triangleIndex];
    Vector finalColor(0, 0, 0);
    for (auto &light : this->scene.lights) {
      Vector lightDirection = light.position - intersectionPoint;
      float sphereRadius = lightDirection.length();
      float sphereArea = 4 * sphereRadius * sphereRadius * (22.0f / 7.0f);
      lightDirection.normalize();
      float angle = std::max(0.0f, lightDirection.dot(triangle.getTriangleNormal()));

      Ray shadowRay(intersectionPoint + triangle.getTriangleNormal() * SHADOW_BIAS, lightDirection);
      bool shadowRayIntersection = hasIntersection(shadowRay);

      Vector lightContribution =
          shadowRayIntersection ? Vector(0, 0, 0)
                                : (static_cast<float>(light.intentsity) / sphereArea * triangle.texture.albedo * angle);
      // std::optional<IntersectionInformation> shadowRayIntersection = trace(shadowRay);

      // Vector lightContribution =
      //     !shadowRayIntersection.has_value() ? Vector(0, 0, 0)
      //                           : (static_cast<float>(light.intentsity) / sphereArea * triangle.texture.albedo *
      //                           angle);
      finalColor += lightContribution;
    }
    return Color(finalColor);
  }
  return this->scene.sceneSettings.sceneBackgroundColor;
}

std::optional<RayTracer::IntersectionInformation> RayTracer::trace(const Ray &ray) const {
  float minDistance = INFINITY;
  std::optional<Vector> intersectionPoint = {};
  size_t intersectedObjectIndex = 0;
  size_t intersectedTriangleIndex = 0;

  for (auto objectIndex = 0; objectIndex < this->scene.objects.size(); objectIndex++) {
    for (auto triangleIndex = 0; triangleIndex < this->scene.objects[objectIndex].triangles.size(); triangleIndex++) {
      std::optional<Vector> tempIntersectionPoint =
          ray.intersectWithTriangle(this->scene.objects[objectIndex].triangles[triangleIndex]);
      if (tempIntersectionPoint.has_value()) {
        float distance = tempIntersectionPoint.value().length();
        if (distance < minDistance) {
          minDistance = distance;
          intersectionPoint = tempIntersectionPoint.value();
          intersectedObjectIndex = objectIndex;
          intersectedTriangleIndex = triangleIndex;
        }
      }
    }
  }
  if (intersectionPoint.has_value()) {
    return IntersectionInformation{intersectionPoint.value(), intersectedObjectIndex, intersectedTriangleIndex};
  }
  return {};
}

bool RayTracer::hasIntersection(const Ray &ray) const {
  float minDistance = INFINITY;
  std::optional<Vector> intersectionPoint = {};

  for (auto objectIndex = 0; objectIndex < this->scene.objects.size(); objectIndex++) {
    for (auto triangleIndex = 0; triangleIndex < this->scene.objects[objectIndex].triangles.size(); triangleIndex++) {
      std::optional<Vector> tempIntersectionPoint =
          ray.intersectWithTriangle(this->scene.objects[objectIndex].triangles[triangleIndex]);
      if (tempIntersectionPoint.has_value()) {
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
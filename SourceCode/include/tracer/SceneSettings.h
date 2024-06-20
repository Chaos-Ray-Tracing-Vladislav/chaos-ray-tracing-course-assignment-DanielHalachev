#pragma once
#include <vector>

#include "tracer/Camera.h"
#include "tracer/Triangle.h"
#include "tracer/Utils.h"

struct Image {
  unsigned int width;
  unsigned int height;
};

struct SceneSettings {
  Color sceneBackgroundColor;
  Image image;
};

struct Mesh {
  std::vector<Triangle> triangles;
};

struct Scene {
  SceneSettings sceneSettings;
  Camera camera;
  std::vector<Mesh> objects;

  const Camera& getCamera() const {
    return this->camera;
  };

  Camera& setCamera() {
    return this->camera;
  };
};
#pragma once
#include <vector>

#include "tracer/Camera.h"
#include "tracer/Triangle.h"
#include "tracer/Utils.h"
#include "tracer/Vector.h"

struct Triangle;
struct Light;

struct Image {
  unsigned int width;
  unsigned int height;
};

struct SceneSettings {
  Color sceneBackgroundColor;
  Image image;
};

struct Light {
  Vector position;
  unsigned int intentsity;
};

struct Mesh {
  std::vector<Triangle> triangles;
};

struct Scene {
  SceneSettings sceneSettings;
  Camera camera;
  std::vector<Light> lights;
  std::vector<Mesh> objects;
};
#pragma once
#include <string>
#include <vector>

#include "tracer/Triangle.h"
class SceneParser {
 public:
  SceneParser();
  [[nodiscard]] static std::vector<Triangle> parseScene(const std::string &pathToScene);
};
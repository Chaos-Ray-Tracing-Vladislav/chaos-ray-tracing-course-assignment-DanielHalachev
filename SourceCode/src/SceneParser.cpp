#include <tracer/SceneParser.h>

#include <fstream>
#include <vector>

#include "tracer/Triangle.h"

SceneParser::SceneParser() = default;

[[nodiscard]] std::vector<Triangle> SceneParser::parseScene(const std::string &pathToScene) {
  std::vector<Triangle> triangles;
  std::ifstream fileReader(pathToScene);
  std::string line;

  while (!fileReader.eof()) {
    Triangle triangle;
    fileReader >> triangle;
    triangles.push_back(triangle);
  }
  triangles.pop_back();
  return triangles;
}
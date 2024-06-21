#pragma once
#include <string>

#include "rapidjson/document.h"
#include "tracer/Camera.h"
#include "tracer/SceneSettings.h"

class SceneParser {
 private:
  static const char* SETTINGS;
  static const char* BG_COLOR;
  static const char* IMAGE_SETTINGS;
  static const char* CAMERA;
  static const char* CAMERA_MATRIX;
  static const char* LIGHTS;
  static const char* LIGHT_INTENSITY;
  static const char* POSITION;
  static const char* SCENE_OBJECTS;
  static const char* VERTICES;
  static const char* TRIANGLES;

  static SceneSettings parseSceneSettings(const rapidjson::Document& document);
  static Camera parseCameraSettings(const rapidjson::Document& document);
  static std::vector<Light> parseLightSettings(const rapidjson::Document& document);
  static std::vector<Mesh> parseSceneObjects(const rapidjson::Document& document);

 public:
  explicit SceneParser();
  static Scene parseScene(const std::string& pathToScene);
};
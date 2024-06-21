#include "tracer/SceneParser.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <fstream>
#include <vector>

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "tracer/SceneSettings.h"
#include "tracer/Vector.h"

const char* SceneParser::SETTINGS = "settings";
const char* SceneParser::BG_COLOR = "background_color";
const char* SceneParser::IMAGE_SETTINGS = "image_settings";
const char* SceneParser::CAMERA = "camera";
const char* SceneParser::CAMERA_MATRIX = "matrix";
const char* SceneParser::LIGHTS = "lights";
const char* SceneParser::LIGHT_INTENSITY = "intensity";
const char* SceneParser::POSITION = "position";
const char* SceneParser::SCENE_OBJECTS = "objects";
const char* SceneParser::VERTICES = "vertices";
const char* SceneParser::TRIANGLES = "triangles";

SceneParser::SceneParser() = default;

Scene SceneParser::parseScene(const std::string& pathToScene) {
  std::ifstream ifs(pathToScene);
  assert(ifs.is_open());

  rapidjson::IStreamWrapper isWrapper(ifs);
  rapidjson::Document document;
  document.ParseStream(isWrapper);

  return Scene{parseSceneSettings(document), parseCameraSettings(document), parseLightSettings(document),
               parseSceneObjects(document)};
};

template <typename T>
std::vector<T> loadIntSTLVector(const rapidjson::Value::ConstArray& array, size_t expectedSize) {
  if (expectedSize != 0) {
    assert(array.Size() == expectedSize);
  }
  std::vector<T> result(expectedSize);
  std::transform(array.begin(), array.end(), result.begin(),
                 [](const auto value) { return static_cast<T>(value.GetUint64()); });
  return result;
}

std::vector<float> loadFloatSTLVector(const rapidjson::Value::ConstArray& array, size_t expectedSize) {
  if (expectedSize != 0) {
    assert(array.Size() == expectedSize);
  }
  std::vector<float> result(expectedSize);
  std::transform(array.begin(), array.end(), result.begin(), [](const auto& value) { return value.GetFloat(); });
  return result;
}

SceneSettings SceneParser::parseSceneSettings(const rapidjson::Document& document) {
  SceneSettings sceneSettings;
  const rapidjson::Value& settingsValue = document.FindMember(SceneParser::SETTINGS)->value;
  if (!settingsValue.IsNull() && settingsValue.IsObject()) {
    const rapidjson::Value& backgroundColorValue = settingsValue.FindMember(SceneParser::BG_COLOR)->value;
    assert(!backgroundColorValue.IsNull() && backgroundColorValue.IsArray());
    auto tempArray = backgroundColorValue.GetArray();
    sceneSettings.sceneBackgroundColor = Color(Vector(loadFloatSTLVector(backgroundColorValue.GetArray(), 3)));

    const rapidjson::Value& imageSettingsValue = settingsValue.FindMember(SceneParser::IMAGE_SETTINGS)->value;
    if (!imageSettingsValue.IsNull() && settingsValue.IsObject()) {
      const rapidjson::Value& imageWidthValue = imageSettingsValue.FindMember("width")->value;
      const rapidjson::Value& imageHeightValue = imageSettingsValue.FindMember("height")->value;
      assert(!imageWidthValue.IsNull() && imageWidthValue.IsInt());
      assert(!imageHeightValue.IsNull() && imageHeightValue.IsInt());
      sceneSettings.image = {imageWidthValue.GetUint(), imageHeightValue.GetUint()};
    }
  }
  return sceneSettings;
}

Camera SceneParser::parseCameraSettings(const rapidjson::Document& document) {
  Camera camera;

  const rapidjson::Value& cameraValue = document.FindMember(SceneParser::CAMERA)->value;
  if (!cameraValue.IsNull() && cameraValue.IsObject()) {
    const rapidjson::Value& cameraPositionValue = cameraValue.FindMember(SceneParser::POSITION)->value;
    assert(!cameraPositionValue.IsNull() && cameraPositionValue.IsArray());
    camera.setPosition() = Vector(loadFloatSTLVector(cameraPositionValue.GetArray(), 3));

    const rapidjson::Value& cameraMatrixValue = cameraValue.FindMember(SceneParser::CAMERA_MATRIX)->value;
    assert(!cameraMatrixValue.IsNull() && cameraMatrixValue.IsArray());
    camera.setRotationMatrix() = Matrix<3>(loadFloatSTLVector(cameraMatrixValue.GetArray(), 9));
  }
  return camera;
}

std::vector<Light> SceneParser::parseLightSettings(const rapidjson::Document& document) {
  std::vector<Light> lights;
  const rapidjson::Value& lightsValue = document.FindMember(SceneParser::LIGHTS)->value;
  if (!lightsValue.IsNull() && lightsValue.IsArray()) {
    lights.reserve(lightsValue.GetArray().Size());
    for (auto& light : lightsValue.GetArray()) {
      const rapidjson::Value& lightIntensityValue = light.FindMember(SceneParser::LIGHT_INTENSITY)->value;
      assert(!lightIntensityValue.IsNull() && lightIntensityValue.IsInt());
      const rapidjson::Value& lightPositionValue = light.FindMember(SceneParser::POSITION)->value;
      assert(!lightPositionValue.IsNull() && lightPositionValue.IsArray());
      Light temp = {Vector(loadFloatSTLVector(lightPositionValue.GetArray(), 3)), lightIntensityValue.GetUint()};
      lights.push_back(temp);
    }
  }
  return lights;
}

std::vector<Mesh> SceneParser::parseSceneObjects(const rapidjson::Document& document) {
  std::vector<Mesh> meshes;

  const rapidjson::Value& objectsValue = document.FindMember(SceneParser::SCENE_OBJECTS)->value;
  if (!objectsValue.IsNull() && objectsValue.IsArray()) {
    meshes.reserve(objectsValue.GetArray().Size());
    for (auto& object : objectsValue.GetArray()) {
      std::vector<Vector> vertices;
      std::vector<size_t> triangleTriples;
      std::vector<Triangle> triangles;

      const rapidjson::Value& verticesValue = object.FindMember(SceneParser::VERTICES)->value;
      assert(!verticesValue.IsNull() && verticesValue.IsArray());
      auto tempArray = verticesValue.GetArray();
      assert(tempArray.Size() % 3 == 0);
      vertices.reserve(tempArray.Size() / 3);
      for (size_t i = 0; i < tempArray.Size(); i += 3) {
        vertices.emplace_back(tempArray[i].GetFloat(), tempArray[i + 1].GetFloat(), tempArray[i + 2].GetFloat());
      }

      const rapidjson::Value& triangleTriplesValue = object.FindMember(SceneParser::TRIANGLES)->value;
      assert(!triangleTriplesValue.IsNull() && triangleTriplesValue.IsArray());
      auto triangleTempArray = triangleTriplesValue.GetArray();
      assert(triangleTempArray.Size() % 3 == 0);
      triangleTriples.reserve(triangleTempArray.Size());
      for (size_t i = 0; i < triangleTempArray.Size(); i++) {
        triangleTriples.push_back(triangleTempArray[i].GetUint64());
      }
      triangles.reserve(triangleTriples.size() / 3);
      for (size_t i = 0; i < triangleTriples.size(); i += 3) {
        std::array<Vector, 3> tempVertexArray;
        tempVertexArray[0] = vertices[triangleTriples[i]];
        tempVertexArray[1] = vertices[triangleTriples[i + 1]];
        tempVertexArray[2] = vertices[triangleTriples[i + 2]];
        triangles.push_back(Triangle(tempVertexArray));
      }
      meshes.push_back(Mesh{triangles});
    }
  }
  return meshes;
}
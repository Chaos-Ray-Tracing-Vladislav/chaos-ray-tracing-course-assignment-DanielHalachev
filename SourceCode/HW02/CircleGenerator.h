#ifndef CIRCLE_GENERATOR_H
#define CIRCLE_GENERATOR_H

#include <cmath>
#include <fstream>
#include <random>

#include "Color.h"

typedef unsigned int uint;
typedef unsigned short ushort;
struct Point {
  int x;
  int y;
};

class CircleGenerator {
 private:
  Point center;
  ushort radius;
  int width;
  int height;
  Color outsideColor;
  Color insideColor;

 public:
  CircleGenerator(Point center, ushort radius, int width, int height) : width(width), height(height), center(center), radius(radius) {
    std::mt19937 rng;
    std::uniform_int_distribution<ushort> colorGenerator = std::uniform_int_distribution<ushort>(0, 255);
    this->insideColor = {0, 0, 0};
    this->outsideColor = {(colorGenerator(rng), colorGenerator(rng), colorGenerator(rng))};
  }
  double distanceBetweenPoints(const Point &a, const Point &b) {
    int deltaX = std::abs(a.x - b.x);
    int deltaY = std::abs(a.y - b.y);
    return std::sqrt(deltaX * deltaX + deltaY * deltaY);
  }
  bool pointInsideCirle(const Point &point) {
    if (distanceBetweenPoints(this->center, point) < static_cast<double>(this->radius)) {
      return true;
    }
    return false;
  }
  void generatePPM(const std::string &filename) {
    std::ofstream outputStream(filename, std::ios_base::trunc);
    outputStream << "P3"
                 << "\n"
                 << this->width << " " << this->height << "\n";
    for (int pixelRow = 0; pixelRow < height; pixelRow++) {
      for (int pixelCol = 0; pixelCol < width; pixelCol++) {
        if (pointInsideCirle({pixelCol, pixelRow})) {
          outputStream << insideColor << "\t";
        } else {
          outputStream << outsideColor << "\t";
        }
      }
      outputStream << "\n";
    }
  }
};
#endif  // CIRCLE_GENERATOR_H
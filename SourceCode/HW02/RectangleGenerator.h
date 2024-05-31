#ifndef RECTANGLE_GENERATOR_H
#define RECTANGLE_GENERATOR_H
#include <fstream>
#include <ios>
#include <ostream>
#include <random>
#include <string>
#include <vector>

#include "Color.h"

#define DEFAULT_COLS 4
#define DEFAULT_ROWS 4
typedef uint uint;
typedef ushort ushort;

class RectangleGenerator {
 private:
  const uint width;
  const uint height;
  std::mt19937 rng;
  std::uniform_int_distribution<ushort> colorGenerator = std::uniform_int_distribution<ushort>(0, 255);
  std::bernoulli_distribution blackChance = std::bernoulli_distribution(0.25);

 public:
  RectangleGenerator(uint width, uint height) : width(width), height(height){};
  void generatePPM(const std::string &filename) {
    std::ofstream outputStream(filename, std::ios_base::trunc);
    outputStream << "P3"
                 << "\n"
                 << this->width << " " << this->height << "\n";

    const uint rectangleWidth = this->width / DEFAULT_COLS;
    const uint rectangleHeight = this->height / DEFAULT_ROWS;
    std::vector<std::vector<Color>> rectangleColors(DEFAULT_ROWS, std::vector<Color>(DEFAULT_COLS));
    for (ushort rectangleRow = 0; rectangleRow < DEFAULT_ROWS; rectangleRow++) {
      for (ushort rectangleCol = 0; rectangleCol < DEFAULT_COLS; rectangleCol++) {
        struct Color color {
          colorGenerator(rng), colorGenerator(rng), colorGenerator(rng)
        };
        rectangleColors[rectangleRow][rectangleCol] = color;
      }
    }

    struct Color black {
      0, 0, 0
    };

    for (ushort rectangleRow = 0; rectangleRow < DEFAULT_ROWS; rectangleRow++) {
      for (uint pixelRow = 0; pixelRow < rectangleHeight; pixelRow++) {
        for (ushort rectangleCol = 0; rectangleCol < DEFAULT_COLS; rectangleCol++) {
          for (uint pixelCol = 0; pixelCol < rectangleWidth; pixelCol++) {
            if (blackChance(rng)) {
              outputStream << black << "\t";
            } else {
              outputStream << rectangleColors[rectangleRow][rectangleCol] << "\t";
            }
          }
        }
        outputStream << "\n";
      }
    }
  }
};
#endif  // RECTANGLE_GENERATOR_H
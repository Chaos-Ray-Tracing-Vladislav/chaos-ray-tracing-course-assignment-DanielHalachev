#include <tracer/Triangle.h>

#include <array>
#include <iostream>
#include <vector>

int main() {
  std::vector<std::pair<Vector, Vector>> vectorPairs = {
      {{3.5, 0, 0}, {1.75, 3.5, 0}},  // 0
      {{3, -3, 1}, {4, 9, 3}},        // 1
      {{3, -3, 1}, {-12, 12, -4}}     // 2
  };

  std::cout << "Task 1\n";
  std::cout << vectorPairs[0].first * vectorPairs[0].second << "\n";
  std::cout << vectorPairs[1].first * vectorPairs[1].second << "\n";

  std::cout << (vectorPairs[1].first * vectorPairs[1].second).length() << "\n";
  std::cout << (vectorPairs[2].first * vectorPairs[2].second).length() << "\n";

  std::vector<std::array<Vector, 3>> vertices = {
      {Vector(-1.75, -1.75, -3), Vector(1.75, -1.75, -3), Vector(0, 1.75, -3)},            // 0
      {Vector(0, 0, -1), Vector(1, 0, 1), Vector(-1, 0, 1)},                               // 1
      {Vector(0.56, 1.11, 1.23), Vector(0.44, -2.386, -0.54), Vector(-1.56, 0.15, -1.92)}  // 2
  };

  std::cout << "Task 2\n";
  for (auto& vertexTriple : vertices) {
    Triangle triangle(vertexTriple);
    Vector normalVector = triangle.getTriangleNormal();
    normalVector.normalize();
    std::cout << normalVector << ", " << triangle.area() << "\n";
    // replace with this to avoid unnecessary computation
    // std::cout << normalVector << ", " << normalVector.length() / 2 << "\n";
  }

  return 0;
}
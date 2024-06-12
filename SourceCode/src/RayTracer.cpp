#include <tracer/RayTracer.h>

#include <fstream>

RayTracer::RayTracer(const Image &image) : image(image) {
  this->pixelRays.resize(this->image.height);
  for (auto &row : this->pixelRays) {
    row.resize(this->image.width);
  }
  this->generateRays();
};

void RayTracer::generateRays() {
  for (unsigned int pixelRow = 0; pixelRow < image.height; pixelRow++) {
    for (unsigned int pixelCol = 0; pixelCol < image.width; pixelCol++) {
      float x = pixelCol + 0.5;
      float y = pixelRow + 0.5;

      x = x / image.width;
      y = y / image.height;

      x = (2.0 * x) - 1.0;
      y = 1 - (2.0 * y);

      x = x * (static_cast<float>(image.width) / static_cast<float>(image.height));

      Vector direction(x, y, -1.0);
      direction.normalize();
      this->pixelRays[pixelRow][pixelCol] = Ray(Vector(0, 0, 0), direction);
    }
  }
}

void RayTracer::generatePPM(const std::string &pathToImage) const {
  std::ofstream outputStream(pathToImage, std::ios_base::trunc);
  outputStream << "P3"
               << "\n"
               << this->image.width << " " << this->image.height << "\n";
  for (unsigned int pixelRow = 0; pixelRow < image.height; pixelRow++) {
    for (unsigned int pixelCol = 0; pixelCol < image.width; pixelCol++) {
      outputStream << this->pixelRays[pixelRow][pixelCol].generateColor() << "\t";
    }
    outputStream << "\n";
  }
}
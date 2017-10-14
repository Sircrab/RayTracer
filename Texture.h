//
// Created by Geno on 13-Oct-17.
//

#ifndef RAYTRACER_TEXTURE_H
#define RAYTRACER_TEXTURE_H
#include <string>
#include <memory>
#include <vector>
#include "Pixel.h"
class Texture{
public:
  unsigned int width;
  unsigned int height;
  std::string extension;
  std::vector<std::vector <Pixel> > colors;
  Texture(std::string fileName){build_from_file(fileName);};
private:
  void build_from_file(const std::string& fileName);
  void read_png(const std::string& fileName);
  void read_jpg(const std::string& fileName);
};
#endif //RAYTRACER_TEXTURE_H

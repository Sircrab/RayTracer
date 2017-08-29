//
// Created by Geno on 29-Aug-17.
//

#ifndef RAYTRACER_UTILS_H
#define RAYTRACER_UTILS_H

#include "Pixel.h"
#include <string>
#include <vector>
namespace utils{
    void generateImage(std::string name, std::vector<std::vector<Pixel> >& preImage, unsigned int width, unsigned int height);
}
#endif //RAYTRACER_UTILS_H

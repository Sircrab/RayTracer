//
// Created by Geno on 29-Aug-17.
//

#ifndef RAYTRACER_UTILS_H
#define RAYTRACER_UTILS_H

#include "Pixel.h"
#include <string>
#include <vector>
class Utils{
public:
    static double exposureTime;
    static void generateImage(std::string name, std::vector<std::vector<Pixel> >& preImage, unsigned int width, unsigned int height);
    static float get_rand();
    static double get_rand_time();
};
#endif //RAYTRACER_UTILS_H

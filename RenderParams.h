//
// Created by Geno on 13-Aug-17.
//

#ifndef RAYTRACER_RENDERPARAMS_H
#define RAYTRACER_RENDERPARAMS_H
#include <string>
struct RenderParams{
    unsigned int width;
    unsigned int height;
    std::string img_title;
    std::string json_file;
    std::string resources_file;
    RenderParams(unsigned int width, unsigned int height, std::string img_title,
                 std::string json_file, std::string resources_file) :
            width(width), height(height), img_title(img_title), json_file(json_file), resources_file(resources_file){};
};
#endif //RAYTRACER_RENDERPARAMS_H

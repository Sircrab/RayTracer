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
    RenderParams(unsigned int width, unsigned int height, std::string img_title, std::string json_file) :
            width(width), height(height), img_title(img_title), json_file(json_file){};
    RenderParams(std::string json_file) : width(512), height(height), img_title("render_res"), json_file(json_file){};
};
#endif //RAYTRACER_RENDERPARAMS_H

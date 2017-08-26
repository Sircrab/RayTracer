//
// Created by Geno on 25-Aug-17.
//

#ifndef RAYTRACER_PARSER_H
#define RAYTRACER_PARSER_H
#include "SceneParams.h"
#include "RenderParams.h"
#include "SceneMaterials.h"
class Parser{
public:
    static RenderParams parse_params(int argc, char* argv[]);
    static SceneMaterials parse_materials(RenderParams renderParams);
    static SceneParams parse_scene(RenderParams renderParams, SceneMaterials sceneMaterials);
};
#endif //RAYTRACER_PARSER_H

//
// Created by Geno on 25-Aug-17.
//

#ifndef RAYTRACER_PARSER_H
#define RAYTRACER_PARSER_H
#include "SceneParams.h"
#include "RenderParams.h"
#include "SceneMaterials.h"
#include <memory>
class Parser{
public:
    static std::shared_ptr<RenderParams> parse_params(int argc, char* argv[]);
    static std::shared_ptr<SceneMaterials> parse_materials(std::shared_ptr<RenderParams> renderParams);
    static std::shared_ptr<SceneParams> parse_scene(std::shared_ptr<RenderParams> renderParams,
                                                          std::shared_ptr<SceneMaterials> sceneMaterials);
};
#endif //RAYTRACER_PARSER_H

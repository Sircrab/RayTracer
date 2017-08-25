//
// Created by Geno on 25-Aug-17.
//

#ifndef RAYTRACER_SCENEMATERIALS_H
#define RAYTRACER_SCENEMATERIALS_H
#include "Materials.h"
#include <string>
#include <unordered_map>
#include <memory>
class SceneMaterials{
public:
    std::unordered_map<std::string, std::shared_ptr<const Material> > materials;
    SceneMaterials(){};
    void add_material(const std::string& name, std::shared_ptr<const Material> m);
};
#endif //RAYTRACER_SCENEMATERIALS_H

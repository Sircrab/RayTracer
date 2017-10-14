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
    std::unordered_map<std::string, std::shared_ptr<const BRDFMaterial> > brdfMats;
    std::unordered_map<std::string, std::shared_ptr<const ReflectiveMaterial> > reflectiveMats;
    std::unordered_map<std::string, std::shared_ptr<const DielectricMaterial> > dielectricMats;
    SceneMaterials(){};
    void add_brdf_material(const std::string& name, std::shared_ptr<const BRDFMaterial> m);
    void add_reflective_material(const std::string& name, std::shared_ptr<const ReflectiveMaterial> m);
    void add_dielectric_material(const std::string& name, std::shared_ptr<const DielectricMaterial> m);
private:
    bool is_free(std::string name);
};
#endif //RAYTRACER_SCENEMATERIALS_H

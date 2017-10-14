//
// Created by Geno on 25-Aug-17.
//
#include "SceneMaterials.h"
#include <iostream>

void SceneMaterials::add_brdf_material(const std::string& name, std::shared_ptr<const ColorBRDFMaterial> m) {
  if(is_free(name)){
    brdfMats[name] = m;
  } else {
    std::cerr << "Repeated name at add_brdf_material" << std::endl;
  }
}

void SceneMaterials::add_reflective_material(const std::string &name, std::shared_ptr<const ReflectiveMaterial> m) {
  if(is_free(name)){
    reflectiveMats[name] = m;
  } else {
    std::cerr << "Repeated name at add_reflective_material" << std::endl;
  }
}

void SceneMaterials::add_dielectric_material(const std::string &name, std::shared_ptr<const DielectricMaterial> m) {
  if(is_free(name)){
    dielectricMats[name] = m;
  } else {
    std::cerr << "Repeated name at adD_dielectric_material" << std::endl;
  }
}

bool SceneMaterials::is_free(std::string name) {
  return brdfMats.count(name) == 0 && reflectiveMats.count(name) == 0 && dielectricMats.count(name) == 0;
}
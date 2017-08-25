//
// Created by Geno on 25-Aug-17.
//
#include "SceneMaterials.h"

void SceneMaterials::add_material(const std::string& name, std::shared_ptr<const Material> m) {
  materials[name] = m;
}


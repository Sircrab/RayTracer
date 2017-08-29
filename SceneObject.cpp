//
// Created by Geno on 25-Aug-17.
//
#include "SceneObject.h"

//When attaching BRDF materials also check for ambient color.
void SceneObject::attach_brdf_material(std::shared_ptr<const BRDFMaterial> m) {
  brdfMats.push_back(m);
  if(m->isAmbient){
    ambientColor = m->baseColor;
  }
}

void SceneObject::attach_reflective_material(std::shared_ptr<const ReflectiveMaterial> m) {
  reflectiveMats.push_back(m);
}

void SceneObject::attach_dielectric_material(std::shared_ptr<const DielectricMaterial> m) {
  dielectricMats.push_back(m);
}


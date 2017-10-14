//
// Created by Geno on 25-Aug-17.
//
#include "SceneObject.h"

//When attaching BRDF materials also check for ambient color.
void SceneObject::attach_brdf_material(std::shared_ptr<const ColorBRDFMaterial> m) {
  brdfMats.push_back(m);
  if(m->isAmbient){
    ambientColor = m->baseColor;
  }
}

void SceneObject::set_reflective_material(std::shared_ptr<const ReflectiveMaterial> m) {
  reflectiveMat = m;
}

void SceneObject::set_dielectric_material(std::shared_ptr<const DielectricMaterial> m) {
  dielectricMat = m;
}


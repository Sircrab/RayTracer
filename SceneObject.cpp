//
// Created by Geno on 25-Aug-17.
//
#include "SceneObject.h"

void SceneObject::attach_material(std::shared_ptr<const Material> m) {
  materials.push_back(m);
  if(m->isAmbient){
    ambientColor = m->baseColor;
  }
}

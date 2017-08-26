//
// Created by Geno on 25-Aug-17.
//
#include "SceneObject.h"

//When attaching materials also check for ambient color.
void SceneObject::attach_material(std::shared_ptr<const Material> m) {
  materials.push_back(m);
  if(m->isAmbient){
    ambientColor = m->baseColor;
  }
}

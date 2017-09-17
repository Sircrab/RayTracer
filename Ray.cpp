//
// Created by Geno on 12-Aug-17.
//

#include "Ray.h"
#include "SceneObject.h"
#include <cmath>

//Double dispatch
bool Ray::intersect_object(const SceneObject &s, Vec3 &out) const {
  return s.intersect_ray(*this,out);
}
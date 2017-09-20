//
// Created by Geno on 20-Sep-17.
//

#ifndef RAYTRACER_RAYCASTHIT_H
#define RAYTRACER_RAYCASTHIT_H
#include "Vec3.h"
#include "SceneObject.h"

struct RayCastHit{
  Vec3 hitPos;
  Vec3 normal;
};
#endif //RAYTRACER_RAYCASTHIT_H
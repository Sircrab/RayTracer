//
// Created by Geno on 21-Sep-17.
//

#ifndef RAYTRACER_AABB_H
#define RAYTRACER_AABB_H
#include "Vec3.h"
#include "Ray.h"

//Axis Aligned Bounding Box
class AABB{
public:
  Vec3 minVec, maxVec;
  AABB(Vec3 minVec, Vec3 maxVec) : minVec(minVec), maxVec(maxVec) {};
  bool intersect_ray(const Ray& ray) const;
};
#endif //RAYTRACER_AABB_H

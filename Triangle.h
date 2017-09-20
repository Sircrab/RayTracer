//
// Created by Geno on 20-Sep-17.
//

#ifndef RAYTRACER_TRIANGLE_H
#define RAYTRACER_TRIANGLE_H
#include "Ray.h"
#include "RayCastHit.h"
class Mesh; //forward declaration
class Triangle{
public:
  unsigned int v0, v1, v2;
  unsigned int n0, n1, n2;
  Triangle(){};
  bool intersect_ray(const Ray& ray,const Mesh& mesh, RayCastHit& out) const;
};
#endif //RAYTRACER_TRIANGLE_H
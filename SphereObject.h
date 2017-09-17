//
// Created by Geno on 17-Sep-17.
//

#ifndef RAYTRACER_SPHEREOBJECT_H
#define RAYTRACER_SPHEREOBJECT_H
#include "SceneObject.h"
class SphereObject : public SceneObject{
public:
  Sphere sphere;
  SphereObject(Sphere sphere) : sphere(sphere), SceneObject(){};
  Vec3 get_normal(const Vec3& pos) const override;
  bool intersect_ray(const Ray& ray, Vec3& out) const override;
};
#endif //RAYTRACER_SPHEREOBJECT_H

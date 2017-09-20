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
  bool intersect_ray(const Ray& ray, RayCastHit& out) const override;
private:
  Vec3 get_normal(const Vec3& pos) const;
};
#endif //RAYTRACER_SPHEREOBJECT_H

//
// Created by Geno on 17-Sep-17.
//

#ifndef RAYTRACER_SPHEREOBJECT_H
#define RAYTRACER_SPHEREOBJECT_H
#include "SceneObject.h"
class SphereObject : public SceneObject{
public:
  Sphere sphere;
  Vec3 velocity;
  SphereObject(Sphere sphere) : sphere(sphere), velocity(Vec3(0.0,0.0,0.0)), SceneObject(){};
  SphereObject(Sphere sphere, Vec3 velocity) : sphere(sphere), velocity(velocity),SceneObject(){};
  bool intersect_ray(const Ray& ray, RayCastHit& out) const override;
private:
  Vec3 get_normal(const Vec3& pos) const;
  Vec2 get_uv(const Vec3& pos) const;
};
#endif //RAYTRACER_SPHEREOBJECT_H

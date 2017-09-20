//
// Created by Geno on 25-Aug-17.
//

#ifndef RAYTRACER_SCENEOBJECT_H
#define RAYTRACER_SCENEOBJECT_H
#include "Sphere.h"
#include "Materials.h"
#include "Color.h"
#include "Ray.h"
#include "RayCastHit.h"
#include <vector>
#include <memory>

class SceneObject{
public:
  std::vector<std::shared_ptr<const BRDFMaterial> > brdfMats;
  std::shared_ptr<const ReflectiveMaterial> reflectiveMat;
  std::shared_ptr<const DielectricMaterial> dielectricMat;
  Color ambientColor = Color(0.0,0.0,0.0);
  void attach_brdf_material(std::shared_ptr<const BRDFMaterial> m);
  void set_reflective_material(std::shared_ptr<const ReflectiveMaterial> m);
  void set_dielectric_material(std::shared_ptr<const DielectricMaterial> m);
  virtual bool intersect_ray(const Ray& ray, RayCastHit& out) const=0;
protected:
  SceneObject(): reflectiveMat(nullptr), dielectricMat(nullptr){};
};
#endif //RAYTRACER_SCENEOBJECT_H

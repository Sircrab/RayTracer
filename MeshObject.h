//
// Created by Geno on 20-Sep-17.
//

#ifndef RAYTRACER_MESHOBJECT_H
#define RAYTRACER_MESHOBJECT_H
#include "SceneObject.h"
#include "Mesh.h"
class MeshObject : public SceneObject{
public:
  Mesh mesh;
  MeshObject(Mesh mesh) : mesh(mesh), SceneObject() {};
  bool intersect_ray(const Ray& ray, RayCastHit& out) const override;
};
#endif //RAYTRACER_MESHOBJECT_H

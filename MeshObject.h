//
// Created by Geno on 20-Sep-17.
//

#ifndef RAYTRACER_MESHOBJECT_H
#define RAYTRACER_MESHOBJECT_H
#include "SceneObject.h"
#include "Mesh.h"
#include "AABB.h"
#include <memory>
class MeshObject : public SceneObject{
public:
  std::shared_ptr<const Mesh> mesh;
  AABB boundingBox;
  MeshObject(std::shared_ptr<const Mesh> mesh, AABB boundingBox, Transform transform) : mesh(mesh), boundingBox(boundingBox),
                                                                 SceneObject(transform) {};
  bool intersect_ray(const Ray& ray, RayCastHit& out) const override;
};
#endif //RAYTRACER_MESHOBJECT_H

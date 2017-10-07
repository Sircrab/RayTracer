//
// Created by Geno on 20-Sep-17.
//

#ifndef RAYTRACER_MESHOBJECT_H
#define RAYTRACER_MESHOBJECT_H
#include "SceneObject.h"
#include "Mesh.h"
#include "AABB.h"
#include "Octree.h"
#include <unordered_set>
#include <memory>
class MeshObject : public SceneObject{
public:
  std::shared_ptr<const Mesh> mesh;
  AABB boundingBox;
  Octree octree;
  MeshObject(std::shared_ptr<const Mesh> mesh, AABB boundingBox, Octree octree, Transform transform) :
    mesh(mesh), boundingBox(boundingBox), octree(octree),SceneObject(transform) {};
  bool intersect_ray(const Ray& ray, RayCastHit& out) const override;
private:
  bool intersect_mesh(const Ray& ray, RayCastHit& out) const;
  void intersect_recursive(const Ray& ray, std::unordered_set<unsigned int>& triSet,
                           std::shared_ptr<OctreeNode> curNode, unsigned int curDepth, std::vector<AABB>& aabbs) const;
};
#endif //RAYTRACER_MESHOBJECT_H

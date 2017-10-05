//
// Created by Geno on 04-Oct-17.
//

#ifndef RAYTRACER_OCTREE_H
#define RAYTRACER_OCTREE_H
#include "OctreeNode.h"
#include "Mesh.h"
#include "AABB.h"
class Octree{
public:
  std::shared_ptr<OctreeNode> root;
  unsigned int maxDepth;
  Octree(unsigned int maxDepth): maxDepth(maxDepth){};
  void build(const std::shared_ptr<Mesh> mesh);
  unsigned int count(std::shared_ptr<OctreeNode> curNode);
private:
  void build_root(const std::shared_ptr<Mesh> mesh);
  void build_recursive(unsigned int curDepth, std::shared_ptr<OctreeNode> curNode, std::shared_ptr<Mesh> mesh);
  std::vector<AABB> generate_octants(const AABB& box);
};
#endif //RAYTRACER_OCTREE_H

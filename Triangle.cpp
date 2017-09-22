//
// Created by Geno on 20-Sep-17.
//
#include "Triangle.h"
#include "Mesh.h"
#include <iostream>
//Based on Moller-Trumbore algorithm.
bool Triangle::intersect_ray(const Ray &ray,std::shared_ptr<const Mesh> mesh,
                             const Transform& transform, RayCastHit &out) const{
  Vec3 transformedV0 = transform.apply(mesh->vertices[v0]);
  Vec3 transformedV1 = transform.apply(mesh->vertices[v1]);
  Vec3 transformedV2 = transform.apply(mesh->vertices[v2]);

  Vec3 v0v1 = transformedV1 - transformedV0;
  Vec3 v0v2 = transformedV2 - transformedV0;
  Vec3 pVec = ray.direction.cross(v0v2);
  double det = v0v1.dot(pVec);
  //No backface culling
  if(det > -Ray::eps && det < -Ray::eps) return false;
  double invDet = 1.0 / det;
  Vec3 tVec = ray.origin - transformedV0;
  double u = tVec.dot(pVec) * invDet; // u parametric coordinate
  if (u < 0 || u > 1) return false; //outside of triangle
  Vec3 qVec = tVec.cross(v0v1);
  double v = ray.direction.dot(qVec) * invDet;
  if (v < 0 || u + v > 1) return false; //outside of triangle

  double t = v0v2.dot(qVec) * invDet;
  if(t < 0) return false;
  out.hitPos = ray.origin + ray.direction * t;
  Vec3 tranformedN0 = transform.apply_normal(mesh->normals[n0]);
  Vec3 transformedN1 = transform.apply_normal(mesh->normals[n1]);
  Vec3 transformedN2 = transform.apply_normal(mesh->normals[n2]);
  out.normal = (transformedN1 * u + transformedN2 * v + tranformedN0 * (1-u-v)).normalize();
  return true;
}

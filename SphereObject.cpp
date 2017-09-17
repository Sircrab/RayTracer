//
// Created by Geno on 17-Sep-17.
//
#include "SphereObject.h"

Vec3 SphereObject::get_normal(const Vec3 &pos) const {
  return (pos - sphere.center).normalize();
}

bool SphereObject::intersect_ray(const Ray &ray, Vec3 &out) const {
  double det = pow(ray.direction.dot(ray.origin - sphere.center),2) -
               pow((ray.origin - sphere.center).magnitude(),2) + pow(sphere.radius,2);
  //1st case: No intersection
  if(det + Ray::eps < 0) return false;
  double ft = -(ray.direction.dot(ray.origin-sphere.center));
  //2nd case: Tangent intersection
  if(det >= -Ray::eps && det <= Ray::eps){
    double d = ft + sqrt(det);
    if(abs(d) - Ray::eps < 0) return false;
    out = ray.origin + ray.direction * d;
    return true;
  }
    //3rd Case: Double intersection
  else{
    double d1 = ft + sqrt(det);
    double d2 = ft - sqrt(det);
    //Assume d1 as smaller, otherwise swap it.
    if(d2 < d1){
      double tmp = d1;
      d1 = d2;
      d2 = tmp;
    }
    if(d1 + Ray::eps < 0){
      if(d2 + Ray::eps < 0){
        return false;
      }
      out = ray.origin + ray.direction * d2;
      return true;
    }
    out = ray.origin + ray.direction * d1;
    return true;
  }
}
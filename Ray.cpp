//
// Created by Geno on 12-Aug-17.
//

#include "Ray.h"
#include <cmath>
//Based on the analytical solution seen in class.
//Returns true if an intersection is found and writes the closes point in out, otherwise it returns false
bool Ray::intersect_sphere(const Sphere& s, Vec3& out) const{
  double det = pow(this->direction.dot(this->origin - s.center),2) -
               pow((this->origin - s.center).magnitude(),2) + pow(s.radius,2);
  double res1 = this->direction.dot(this->origin - s.center);
  //1st case: No intersection
  if(det + eps < 0) return false;
  double ft = -(this->direction.dot(this->origin-s.center));
  //2nd case: Tangent intersection
  if(det >= -eps && det <= eps){
    double d = ft + sqrt(det);
    if(abs(d) - eps < 0) return false;
    out = this->origin + this->direction * d;
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
    if(d1 + eps < 0){
      if(d2 + eps < 0){
        return false;
      }
      out = this->origin + this->direction * d2;
      return true;
    }
    out = this->origin + this->direction * d1;
    return true;
  }
}
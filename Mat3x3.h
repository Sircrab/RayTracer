//
// Created by Geno on 21-Sep-17.
//

#ifndef RAYTRACER_MAT3X3_H
#define RAYTRACER_MAT3X3_H
#include "Vec3.h"
class Mat3x3{
public:
  double mat[3][3];
  Mat3x3(double m11, double m12, double m13, double m21, double m22, double m23,
         double m31, double m32, double m33);
  static Vec3 vec_mul(const Mat3x3& a, const Vec3& b);
  Vec3 operator*(const Vec3& other) const;
};
#endif //RAYTRACER_MAT3X3_H

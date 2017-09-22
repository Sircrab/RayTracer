//
// Created by Geno on 21-Sep-17.
//

#ifndef RAYTRACER_MAT4X4_H
#define RAYTRACER_MAT4X4_H
#include "Vec4.h"
class Mat4x4{
public:
  double mat[4][4];
  Mat4x4(double m11, double m12, double m13, double m14, double m21, double m22, double m23, double m24,
  double m31, double m32, double m33, double m34, double m41, double m42, double m43, double m44);
  Mat4x4();
  static Vec4 vec_mul(const Mat4x4& a, const Vec4& b);
  static Mat4x4 mat_mul(const Mat4x4& a, const Mat4x4& b);
  static Mat4x4 transpose(const Mat4x4& a);
  static double determinant(const Mat4x4& a);
  static Mat4x4 inverse(const Mat4x4& a);
  Vec4 operator*(const Vec4& other) const;
  Mat4x4 operator*(const Mat4x4& other) const;
  Mat4x4 transpose();
  double determinant() const;
  Mat4x4 inverse() const;
private:
  static double cell_mul(const Mat4x4& a, const Mat4x4& b, unsigned int i, unsigned int j);
};
#endif //RAYTRACER_MAT4X4_H

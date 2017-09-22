//
// Created by Geno on 21-Sep-17.
//

#include "Mat3x3.h"

Mat3x3::Mat3x3(double m11, double m12, double m13, double m21, double m22, double m23,
               double m31, double m32, double m33) {
  mat[0][0] = m11; mat[0][1] = m12; mat[0][2] = m13;
  mat[1][0] = m21; mat[1][1] = m22; mat[1][2] = m23;
  mat[2][0] = m31; mat[2][1] = m32; mat[2][2] = m33;

}

Vec3 Mat3x3::vec_mul(const Mat3x3 &a, const Vec3 &b) {
  double vecRes[3] = {0.0,0.0,0.0};
  double vecArr[3] = {b.x,b.y,b.z};
  for(int i = 0 ; i < 3; i++){
    for(int j = 0; j < 3; j++){
      vecRes[i] += vecArr[i]*a.mat[i][j];
    }
  }
  return Vec3(vecRes[0], vecRes[1], vecRes[2]);
}

Vec3 Mat3x3::operator*(const Vec3 &other) const{
  return Mat3x3::vec_mul(*this,other);
}

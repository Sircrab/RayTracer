//
// Created by Geno on 21-Sep-17.
//
#include "Mat4x4.h"

Mat4x4::Mat4x4(double m11, double m12, double m13, double m14, double m21, double m22, double m23, double m24,
               double m31, double m32, double m33, double m34, double m41, double m42, double m43, double m44) {
  mat[0][0] = m11; mat[0][1] = m12; mat[0][2] = m13 ;mat[0][3] = m14;
  mat[1][0] = m21; mat[1][1] = m22; mat[1][2] = m23 ;mat[1][3] = m24;
  mat[2][0] = m31; mat[2][1] = m32; mat[2][2] = m33 ;mat[2][3] = m34;
  mat[3][0] = m41; mat[3][1] = m42; mat[3][2] = m43 ;mat[3][3] = m44;

}

Mat4x4::Mat4x4(){
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      if(i == j){
        mat[i][j] == 1.0;
      } else{
        mat[i][j] = 0.0;
      }
    }
  }
}

Vec4 Mat4x4::vec_mul(const Mat4x4 &a, const Vec4 &b) {
  double vecRes[4] = {0.0,0.0,0.0,0.0};
  double vecArr[4] = {b.x,b.y,b.z,b.w};
  for(int i = 0 ; i < 4; i++){
    for(int j = 0; j < 4; j++){
      vecRes[i] += vecArr[j]*a.mat[i][j];
    }
  }
  return Vec4(vecRes[0], vecRes[1], vecRes[2], vecRes[3]);
}

Mat4x4 Mat4x4::transpose(const Mat4x4& a) {
  double tmpMat[4][4];
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      tmpMat[i][j] = a.mat[j][i];
    }
  }
  return Mat4x4(tmpMat[0][0],tmpMat[0][1],tmpMat[0][2],tmpMat[0][3],
                tmpMat[1][0],tmpMat[1][1],tmpMat[1][2],tmpMat[1][3],
                tmpMat[2][0],tmpMat[2][1],tmpMat[2][2],tmpMat[2][3],
                tmpMat[3][0],tmpMat[3][1],tmpMat[3][2],tmpMat[3][3]);
}

double Mat4x4::determinant(const Mat4x4 &a) {
  return
    (a.mat[0][0]*a.mat[1][1]*a.mat[2][2]*a.mat[3][3]) + (a.mat[0][0]*a.mat[1][2]*a.mat[2][3]*a.mat[3][1]) + (a.mat[0][0]*a.mat[1][3]*a.mat[2][1]*a.mat[3][2]) +
    (a.mat[0][1]*a.mat[1][0]*a.mat[2][3]*a.mat[3][2]) + (a.mat[0][1]*a.mat[1][2]*a.mat[2][0]*a.mat[3][3]) + (a.mat[0][1]*a.mat[1][3]*a.mat[2][2]*a.mat[3][0]) +
    (a.mat[0][2]*a.mat[1][0]*a.mat[2][1]*a.mat[3][3]) + (a.mat[0][2]*a.mat[1][1]*a.mat[2][3]*a.mat[3][0]) + (a.mat[0][2]*a.mat[1][3]*a.mat[2][0]*a.mat[3][1]) +
    (a.mat[0][3]*a.mat[1][0]*a.mat[2][2]*a.mat[3][1]) + (a.mat[0][3]*a.mat[1][1]*a.mat[2][0]*a.mat[3][2]) + (a.mat[0][3]*a.mat[1][2]*a.mat[2][1]*a.mat[3][0]) -
    (a.mat[0][0]*a.mat[1][1]*a.mat[2][3]*a.mat[3][2]) - (a.mat[0][0]*a.mat[1][2]*a.mat[2][1]*a.mat[3][3]) - (a.mat[0][0]*a.mat[1][3]*a.mat[2][2]*a.mat[3][1]) -
    (a.mat[0][1]*a.mat[1][0]*a.mat[2][2]*a.mat[3][3]) - (a.mat[0][1]*a.mat[1][2]*a.mat[2][3]*a.mat[3][0]) - (a.mat[0][1]*a.mat[1][3]*a.mat[2][0]*a.mat[3][2]) -
    (a.mat[0][2]*a.mat[1][0]*a.mat[2][3]*a.mat[3][1]) - (a.mat[0][2]*a.mat[1][1]*a.mat[2][0]*a.mat[3][3]) - (a.mat[0][2]*a.mat[1][3]*a.mat[2][1]*a.mat[3][0]) -
    (a.mat[0][3]*a.mat[1][0]*a.mat[2][1]*a.mat[3][2]) - (a.mat[0][3]*a.mat[1][1]*a.mat[2][2]*a.mat[3][0]) - (a.mat[0][3]*a.mat[1][2]*a.mat[2][0]*a.mat[3][1]);

}

Mat4x4 Mat4x4::inverse(const Mat4x4 &a) {
  double det = a.determinant();
  if(det != 0){
    double tmpMat[4][4];
    tmpMat[0][0] = (a.mat[1][1]*a.mat[2][2]*a.mat[3][3]) + (a.mat[1][2]*a.mat[2][3]*a.mat[3][1]) + (a.mat[1][3]*a.mat[2][1]*a.mat[3][2]) -
      (a.mat[1][1]*a.mat[2][3]*a.mat[3][2]) - (a.mat[1][2]*a.mat[2][1]*a.mat[3][3]) - (a.mat[1][3]*a.mat[2][2]*a.mat[3][1]);
    tmpMat[0][1] = (a.mat[0][1]*a.mat[2][3]*a.mat[3][2]) + (a.mat[0][2]*a.mat[2][1]*a.mat[3][3]) + (a.mat[0][3]*a.mat[2][2]*a.mat[3][1]) -
      (a.mat[0][1]*a.mat[2][2]*a.mat[3][3]) - (a.mat[0][2]*a.mat[2][3]*a.mat[3][1]) - (a.mat[0][3]*a.mat[2][1]*a.mat[3][2]);
    tmpMat[0][2] = (a.mat[0][1]*a.mat[1][2]*a.mat[3][3]) + (a.mat[0][2]*a.mat[1][3]*a.mat[3][1]) + (a.mat[0][3]*a.mat[1][1]*a.mat[3][2]) -
      (a.mat[0][1]*a.mat[1][3]*a.mat[3][2]) - (a.mat[0][2]*a.mat[1][1]*a.mat[3][3]) - (a.mat[0][3]*a.mat[1][2]*a.mat[3][1]);
    tmpMat[0][3] = (a.mat[0][1]*a.mat[1][3]*a.mat[2][2]) + (a.mat[0][2]*a.mat[1][1]*a.mat[2][3]) + (a.mat[0][3]*a.mat[1][2]*a.mat[2][1]) -
      (a.mat[0][1]*a.mat[1][2]*a.mat[2][3]) - (a.mat[0][2]*a.mat[1][3]*a.mat[2][1]) - (a.mat[0][3]*a.mat[1][1]*a.mat[2][2]);
    tmpMat[1][0] = (a.mat[1][0]*a.mat[2][3]*a.mat[3][2]) + (a.mat[1][2]*a.mat[2][0]*a.mat[3][3]) + (a.mat[1][3]*a.mat[2][2]*a.mat[3][0]) -
                   (a.mat[1][0]*a.mat[2][2]*a.mat[3][3]) - (a.mat[1][2]*a.mat[2][3]*a.mat[3][0]) - (a.mat[1][3]*a.mat[2][0]*a.mat[3][2]);
    tmpMat[1][1] = (a.mat[0][0]*a.mat[2][2]*a.mat[3][3]) + (a.mat[0][2]*a.mat[2][3]*a.mat[3][0]) + (a.mat[0][3]*a.mat[2][0]*a.mat[3][2]) -
                   (a.mat[0][0]*a.mat[2][3]*a.mat[3][2]) - (a.mat[0][2]*a.mat[2][0]*a.mat[3][3]) - (a.mat[0][3]*a.mat[2][2]*a.mat[3][0]);
    tmpMat[1][2] = (a.mat[0][0]*a.mat[1][3]*a.mat[3][2]) + (a.mat[0][2]*a.mat[1][0]*a.mat[3][3]) + (a.mat[0][3]*a.mat[1][2]*a.mat[3][0]) -
                   (a.mat[0][0]*a.mat[1][2]*a.mat[3][3]) - (a.mat[0][2]*a.mat[1][3]*a.mat[3][0]) - (a.mat[0][3]*a.mat[1][0]*a.mat[3][2]);
    tmpMat[1][3] = (a.mat[0][0]*a.mat[1][2]*a.mat[2][3]) + (a.mat[0][2]*a.mat[1][3]*a.mat[2][0]) + (a.mat[0][3]*a.mat[1][0]*a.mat[2][2]) -
                   (a.mat[0][0]*a.mat[1][3]*a.mat[2][2]) - (a.mat[0][2]*a.mat[1][0]*a.mat[2][3]) - (a.mat[0][3]*a.mat[1][2]*a.mat[2][0]);
    tmpMat[2][0] = (a.mat[1][0]*a.mat[2][1]*a.mat[3][3]) + (a.mat[1][1]*a.mat[2][3]*a.mat[3][0]) + (a.mat[1][3]*a.mat[2][0]*a.mat[3][1]) -
                   (a.mat[1][0]*a.mat[2][3]*a.mat[3][1]) - (a.mat[1][1]*a.mat[2][0]*a.mat[3][3]) - (a.mat[1][3]*a.mat[2][1]*a.mat[3][0]);
    tmpMat[2][1] = (a.mat[0][0]*a.mat[2][3]*a.mat[3][1]) + (a.mat[0][1]*a.mat[2][0]*a.mat[3][3]) + (a.mat[0][3]*a.mat[2][1]*a.mat[3][0]) -
                   (a.mat[0][0]*a.mat[2][1]*a.mat[3][3]) - (a.mat[0][1]*a.mat[2][3]*a.mat[3][0]) - (a.mat[0][3]*a.mat[2][0]*a.mat[3][1]);
    tmpMat[2][2] = (a.mat[0][0]*a.mat[1][1]*a.mat[3][3]) + (a.mat[0][1]*a.mat[1][3]*a.mat[3][0]) + (a.mat[0][3]*a.mat[1][0]*a.mat[3][1]) -
                   (a.mat[0][0]*a.mat[1][3]*a.mat[3][1]) - (a.mat[0][1]*a.mat[1][0]*a.mat[3][3]) - (a.mat[0][3]*a.mat[1][1]*a.mat[3][0]);
    tmpMat[2][3] = (a.mat[0][0]*a.mat[1][3]*a.mat[2][1]) + (a.mat[0][1]*a.mat[1][0]*a.mat[2][3]) + (a.mat[0][3]*a.mat[1][1]*a.mat[2][0]) -
                   (a.mat[0][0]*a.mat[1][1]*a.mat[2][3]) - (a.mat[0][1]*a.mat[1][3]*a.mat[2][0]) - (a.mat[0][3]*a.mat[1][0]*a.mat[2][1]);
    tmpMat[3][0] = (a.mat[1][0]*a.mat[2][2]*a.mat[3][1]) + (a.mat[1][1]*a.mat[2][0]*a.mat[3][2]) + (a.mat[1][2]*a.mat[2][1]*a.mat[3][0]) -
                   (a.mat[1][0]*a.mat[2][1]*a.mat[3][2]) - (a.mat[1][1]*a.mat[2][2]*a.mat[3][0]) - (a.mat[1][2]*a.mat[2][0]*a.mat[3][1]);
    tmpMat[3][1] = (a.mat[0][0]*a.mat[2][1]*a.mat[3][2]) + (a.mat[0][1]*a.mat[2][2]*a.mat[3][0]) + (a.mat[0][2]*a.mat[2][0]*a.mat[3][1]) -
                   (a.mat[0][0]*a.mat[2][2]*a.mat[3][1]) - (a.mat[0][1]*a.mat[2][0]*a.mat[3][2]) - (a.mat[0][2]*a.mat[2][1]*a.mat[3][0]);
    tmpMat[3][2] = (a.mat[0][0]*a.mat[1][2]*a.mat[3][1]) + (a.mat[0][1]*a.mat[1][0]*a.mat[3][2]) + (a.mat[0][2]*a.mat[1][1]*a.mat[3][0]) -
                   (a.mat[0][0]*a.mat[1][1]*a.mat[3][2]) - (a.mat[0][1]*a.mat[1][2]*a.mat[3][0]) - (a.mat[0][2]*a.mat[1][0]*a.mat[3][1]);
    tmpMat[3][3] = (a.mat[0][0]*a.mat[1][1]*a.mat[2][2]) + (a.mat[0][1]*a.mat[1][2]*a.mat[2][0]) + (a.mat[0][2]*a.mat[1][0]*a.mat[2][1]) -
                   (a.mat[0][0]*a.mat[1][2]*a.mat[2][1]) - (a.mat[0][1]*a.mat[1][0]*a.mat[2][2]) - (a.mat[0][2]*a.mat[1][1]*a.mat[2][0]);
    for(int i = 0; i < 4; i++){
      for(int j = 0; j < 4; j++){
        tmpMat[i][j] /= det;
      }
    }
    return Mat4x4(tmpMat[0][0],tmpMat[0][1],tmpMat[0][2],tmpMat[0][3],
                   tmpMat[1][0],tmpMat[1][1],tmpMat[1][2],tmpMat[1][3],
                   tmpMat[2][0],tmpMat[2][1],tmpMat[2][2],tmpMat[2][3],
                   tmpMat[3][0],tmpMat[3][1],tmpMat[3][2],tmpMat[3][3]);
  }
  return Mat4x4();
}

double Mat4x4::cell_mul(const Mat4x4 &a, const Mat4x4 &b, unsigned int i, unsigned int j) {
  double res = 0;
  for(int k = 0 ; k < 4; k++){
    res += a.mat[i][k] * b.mat[k][j];
  }
  return res;
}

Mat4x4 Mat4x4::mat_mul(const Mat4x4 &a, const Mat4x4 &b) {
  double tmpMat[4][4];
  for(unsigned int i = 0; i < 4; i++){
    for(unsigned int j = 0 ; j < 4; j++){
      tmpMat[i][j] = cell_mul(a,b,i,j);
    }
  }
  return Mat4x4(tmpMat[0][0],tmpMat[0][1],tmpMat[0][2],tmpMat[0][3],
                tmpMat[1][0],tmpMat[1][1],tmpMat[1][2],tmpMat[1][3],
                tmpMat[2][0],tmpMat[2][1],tmpMat[2][2],tmpMat[2][3],
                tmpMat[3][0],tmpMat[3][1],tmpMat[3][2],tmpMat[3][3]);
}

Vec4 Mat4x4::operator*(const Vec4 &other) const{
  return Mat4x4::vec_mul(*this,other);
}

Mat4x4 Mat4x4::operator*(const Mat4x4 &other) const {
  return mat_mul(*this,other);
}

Mat4x4 Mat4x4::transpose() {
  return Mat4x4::transpose(*this);
}

double Mat4x4::determinant() const{
  return Mat4x4::determinant(*this);
}

Mat4x4 Mat4x4::inverse() const {
  return Mat4x4::inverse(*this);
}

//
// Created by Geno on 21-Sep-17.
//
#include "Transform.h"
#include <cmath>

Transform::Transform() : position(Vec4(0.0,0.0,0.0,1.0)), rotation(Vec4(0.0,0.0,0.0,1.0)), scale(Vec4(1.0,1.0,1.0,1.0)),
                         transformMat(generate_transform_mat()) {
  normalTransformMat = transformMat.inverse().transpose();
};

Transform::Transform(Vec3 position, Vec3 rotation, Vec3 scale)  :
  position(Vec4(position.x, position.y, position.z, 1.0)), rotation(Vec4(rotation.x, rotation.y, rotation.z, 1.0)),
  scale(Vec4(scale.x, scale.y, scale.z, 1.0)), transformMat(generate_transform_mat()){
  normalTransformMat = transformMat.inverse().transpose();
};

Mat4x4 Transform::generate_pos_mat() const{
  return Mat4x4(1.0,0.0,0.0,position.x,
                  0.0,1.0,0.0,position.y,
                  0.0,0.0,1.0,position.z,
                  0.0,0.0,0.0,1.0);
}

Mat4x4 Transform::generate_rot_x_mat() const{
  return Mat4x4(1.0, 0.0, 0.0, 0.0,
                  0.0, std::cos(rotation.x * (180.0/M_PI)), -std::sin(rotation.x * (180.0/M_PI)), 0.0,
                  0.0, std::sin(rotation.x * (180.0/M_PI)), std::cos(rotation.x * (180.0/M_PI)), 0.0,
                  0.0, 0.0, 0.0, 1.0);
}

Mat4x4 Transform::generate_rot_y_mat() const{
  return Mat4x4(std::cos(rotation.y * (180.0/M_PI)), 0.0, std::sin(rotation.y * (180.0/M_PI)),0.0,
                  0.0, 1.0, 0.0,0.0,
                  -std::sin(rotation.y * (180.0/M_PI)),0.0, std::cos(rotation.y * (180.0/M_PI)),0.0,
                  0.0,0.0,0.0,1.0);
}

Mat4x4 Transform::generate_rot_z_mat() const{
  return Mat4x4(std::cos(rotation.z * (180.0/M_PI)), -std::sin(rotation.z * (180.0/M_PI)), 0.0, 0.0,
                  std::sin(rotation.z * (180.0/M_PI)), std::cos(rotation.z * (180.0/M_PI)), 0.0, 0.0,
                  0.0, 0.0, 1.0, 0.0,
                  0.0,0.0,0.0,1.0);
}

Mat4x4 Transform::generate_scale_mat() const{
  return Mat4x4(scale.x, 0.0, 0.0, 0.0,
                  0.0,scale.y, 0.0, 0.0,
                  0.0,0.0,scale.z, 0.0,
                  0.0,0.0,0.0,1.0);
}

Mat4x4 Transform::generate_transform_mat() const {
  return generate_pos_mat() * (generate_rot_z_mat() * (generate_rot_y_mat() * (generate_rot_x_mat() * generate_scale_mat())));
}

Vec3 Transform::apply(const Vec3 &other) const {
  Vec4 toVec4(other.x,other.y,other.z,1.0);
  toVec4 = transformMat * toVec4;
  return Vec3(toVec4.x, toVec4.y, toVec4.z);
}

Vec3 Transform::apply_normal(const Vec3 &normal) const {
  Vec4 toVec4(normal.x,normal.y,normal.z,1.0);
  toVec4 = normalTransformMat * toVec4;
  return Vec3(toVec4.x, toVec4.y, toVec4.z);
}

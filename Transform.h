//
// Created by Geno on 21-Sep-17.
//

#ifndef RAYTRACER_TRANSFORM_H
#define RAYTRACER_TRANSFORM_H
#include "Vec3.h"
#include "Mat3x3.h"
#include "Vec4.h"
#include "Mat4x4.h"
class Transform{
public:
  Vec4 position, rotation, scale;

  Transform();
  Transform(Vec3 position, Vec3 rotation, Vec3 scale);
  Vec3 apply(const Vec3& other) const;
  Vec3 apply_normal(const Vec3& normal) const;
private:
  Mat4x4 transformMat, normalTransformMat;
  Mat4x4 generate_transform_mat() const;
  Mat4x4 generate_pos_mat() const;
  Mat4x4 generate_rot_x_mat() const;
  Mat4x4 generate_rot_y_mat() const;
  Mat4x4 generate_rot_z_mat() const;
  Mat4x4 generate_scale_mat() const;
};
#endif //RAYTRACER_TRANSFORM_H

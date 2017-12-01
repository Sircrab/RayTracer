//
// Created by sircrab on 30-11-17.
//

#ifndef RAYTRACER_LENSCAMERA_H
#define RAYTRACER_LENSCAMERA_H
#include "Camera.h"
class LensCamera : public Camera{
public:
  LensCamera(double cam_fov, Vec3 cam_up, Vec3 cam_pos, Vec3 cam_target,unsigned int scr_width,unsigned int scr_height,
            double focalDistance, double lensSize, double exposure);
  double get_top() const override;
  double get_left() const override;
  double get_right() const override;
  double get_bottom() const override;
  Vec3 get_w() const override;
  Vec3 get_u() const override;
  Vec3 get_v() const override;
  double get_near() const override;
  Vec3 get_position() const override;
  Vec3 get_orig_position() const override;
protected:
  double focalDistance;
  double lensSize;
  double exposure;

};
#endif //RAYTRACER_LENSCAMERA_H

//
// Created by sircrab on 30-11-17.
//

#include "LensCamera.h"
#include <cmath>
#include "Utils.h"

LensCamera::LensCamera(double cam_fov, Vec3 cam_up, Vec3 cam_pos, Vec3 cam_target, unsigned int scr_width,
                              unsigned int scr_height, double focalDistance, double lensSize, double exposure) :
                      Camera(cam_fov, cam_up, cam_pos, cam_target, scr_width, scr_height),
                      focalDistance(focalDistance), lensSize(lensSize), exposure(exposure) {
  top = focalDistance * tan((cam_fov * M_PI/180)/2);
  bottom = -top;
  right = top * (scr_width * 1.0 / scr_height);
  left = -right;
  w = (cam_pos - cam_target).normalize();
  u = cam_up.cross(w).normalize();
  v = w.cross(u).normalize();
  Utils::exposureTime = exposure;
}

double LensCamera::get_top() const {return top;}
double LensCamera::get_bottom() const {return bottom;}
double LensCamera::get_left() const {return left;}
double LensCamera::get_right() const {return right;}
Vec3 LensCamera::get_u() const {return u;}
Vec3 LensCamera::get_v() const {return v;}
Vec3 LensCamera::get_w() const {return w;}
double LensCamera::get_near() const {return focalDistance;}
Vec3 LensCamera::get_position() const {
  return cam_pos + (u * lensSize * Utils::get_rand()) + (v * lensSize * Utils::get_rand());
}
Vec3 LensCamera::get_orig_position() const {return cam_pos;}
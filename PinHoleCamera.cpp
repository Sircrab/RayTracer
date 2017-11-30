//
// Created by Geno on 13-Aug-17.
//

#include "PinHoleCamera.h"
#include <cmath>


PinHoleCamera::PinHoleCamera(double cam_fov, Vec3 cam_up, Vec3 cam_pos, Vec3 cam_target,
               unsigned int scr_width, unsigned int scr_height) :
  Camera(cam_fov, cam_up, cam_pos, cam_target, scr_width, scr_height) {
  top = near * tan((cam_fov * M_PI/180)/2);
  bottom = -top;
  right = top * (scr_width * 1.0 / scr_height);
  left = -right;
  w = (cam_pos - cam_target).normalize();
  u = cam_up.cross(w).normalize();
  v = w.cross(u).normalize();
};

double PinHoleCamera::get_top() const {return top;}
double PinHoleCamera::get_bottom() const {return bottom;}
double PinHoleCamera::get_left() const {return left;}
double PinHoleCamera::get_right() const {return right;}
Vec3 PinHoleCamera::get_u() const {return u;}
Vec3 PinHoleCamera::get_v() const {return v;}
Vec3 PinHoleCamera::get_w() const {return w;}
double PinHoleCamera::get_near() const {return near;}
Vec3 PinHoleCamera::get_position() const {return cam_pos;}
Vec3 PinHoleCamera::get_orig_position() const {return cam_pos;}



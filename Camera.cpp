//
// Created by Geno on 13-Aug-17.
//

#include "Camera.h"
#include <cmath>
//IMPORTANT: HERE NEAR IS ASSUMED AS 0.1 (NOT SPECIFIED IN DESCRIPTION)
Camera::Camera(double cam_fov, Vec3 cam_up, Vec3 cam_pos, Vec3 cam_target,
               unsigned int scr_width, unsigned int scr_height) :
        cam_fov(cam_fov), cam_up(cam_up), cam_pos(cam_pos) ,
        cam_target(cam_target), scr_width(scr_width), scr_height(scr_height) {
  top = 0.1 * tan((cam_fov * M_PI/180)/2);
  bottom = -top;
  right = top * (scr_width * 1.0 / scr_height);
  left = -right;
  w = (cam_pos - cam_target).normalize();
  u = cam_up.cross(w).normalize();
  v = w.cross(u).normalize();
};

double Camera::get_top() {return top;}
double Camera::get_bottom() {return bottom;}
double Camera::get_left() {return left;}
double Camera::get_right() {return right;}
Vec3 Camera::get_u() {return u;}
Vec3 Camera::get_v() {return v;}
Vec3 Camera::get_w() {return w;}



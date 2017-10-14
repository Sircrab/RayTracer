//
// Created by Geno on 14-Oct-17.
//

#include "Vec2.h"
#include "Vec3.h"
#include <cmath>
#include <sstream>

Vec2 Vec2::add(const Vec2 &a, const Vec2 &b) {
  return Vec2(a.x + b.x, a.y + b.y);
}

Vec2 Vec2::sub(const Vec2 &a, const Vec2 &b) {
  return Vec2(a.x - b.x, a.y - b.y);
}

Vec2 Vec2::mul(const Vec2 &a, const Vec2 &b) {
  return Vec2(a.x * b.x, a.y * b.y);
}

Vec2 Vec2::div(const Vec2 &a, const Vec2 &b) {
  return Vec2(a.x / b.x, a.y / b.y);
}

Vec2 Vec2::scalar_mul(const Vec2 &a, double b) {
  return Vec2(a.x * b, a.y * b);
}

double Vec2::dot(const Vec2 &a, const Vec2 &b) {
  return (a.x * b.x) + (a.y * b.y);
}

double Vec2::cross(const Vec2 &a, const Vec2 &b) {
  return Vec3(a.x,a.y,0).cross(Vec3(b.x,b.y,0)).z;
}

Vec2 Vec2::operator+(const Vec2& other) const{
  return Vec2::add(*this,other);
}

Vec2 Vec2::operator-(const Vec2& other) const{
  return Vec2::sub(*this,other);
}

Vec2 Vec2::operator-() const{
  return Vec2(-this->x,-this->y);
}

Vec2 Vec2::operator*(const Vec2& other) const{
  return Vec2::mul(*this,other);
}

Vec2 Vec2::operator/(const Vec2 &other) const {
  return Vec2::div(*this,other);
}

Vec2 Vec2::operator*(double lambda) const{
  return Vec2::scalar_mul(*this,lambda);
}

Vec2 Vec2::operator+=(const Vec2& other){
  this->x = this->x + other.x;
  this->y = this->y + other.y;
  return *this;
}

double Vec2::operator[](const int idx) const {
  switch(idx){
    case 0:
      return x;
    case 1:
      return y;
    default:
      return -1;
  }
}

double Vec2::magnitude() const{
  return std::sqrt(this->x * this->x + this->y * this->y);
}

Vec2 Vec2::normalize() const{
  return Vec2(this->x/this->magnitude(),this->y/this->magnitude());
}

double Vec2::dot(const Vec2 &other) const{
  return Vec2::dot(*this,other);
}

double Vec2::cross(const Vec2 &other) const{
  return Vec2::cross(*this,other);
}

std::string Vec2::to_string() const{
  std::ostringstream ss;
  ss << "(" << this->x << ", " << this->y << ")";
  return ss.str();
}






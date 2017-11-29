//
// Created by Geno on 24-Aug-17.
//

#include "Color.h"

Color::Color() : color(0.0,0.0,0.0){}

Color::Color(double r, double g, double b) : color(r,g,b) {}

Color Color::clamp(const Color &other) {
  return Color(std::min(std::max(other.color.x,0.0),1.0),
               std::min(std::max(other.color.y,0.0),1.0),std::min(std::max(other.color.z,0.0),1.0));
}

Color Color::add(const Color &a, const Color &b) {
  return Color(a.color.x + b.color.x, a.color.y + b.color.y, a.color.z + b.color.z).clamp();
}

Color Color::sub(const Color &a, const Color &b) {
  return Color(a.color.x - b.color.x, a.color.y - b.color.y, a.color.z - b.color.z).clamp();
}

Color Color::mul(const Color &a, const Color &b) {
  return Color(a.color.x * b.color.x, a.color.y * b.color.y, a.color.z * b.color.z).clamp();
}

Color Color::div(const Color &a, const double b) {
  return Color(a.color.x / b, a.color.y / b, a.color.z / b).clamp();
}

Color Color::scalar_mul(const Color &a, double lambda) {
  return Color(lambda * a.color.x, lambda * a.color.y, lambda * a.color.z).clamp();
}

Color Color::operator+(const Color &other) const{
  return add(*this,other);
}

Color Color::operator-(const Color &other) const{
  return sub(*this,other);
}

Color Color::operator*(const Color &other) const{
  return mul(*this,other);
}

Color Color::operator*(double lambda) const{
  return scalar_mul(*this,lambda);
}

Color Color::operator/(double lambda) {
  return div(*this, lambda);
}

Color& Color::operator+=(const Color& other) {
  this->color = ((*this) + other).color;
  return *this;
}

Color Color::clamp(){
  return clamp(*this);
}

Vec3 Color::to_Vec3() const{
  return color;
}

double Color::r() const{
  return color.x;
}

double Color::g() const{
  return color.y;
}

double Color::b() const{
  return color.z;
}
//
// Created by Geno on 24-Aug-17.
//

#include "Color.h"

Color::Color() : color(0,0,0){}

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

Color Color::scalar_mul(const Color &a, double lambda) {
  return Color(lambda * a.color.x, lambda * a.color.y, lambda * a.color.z).clamp();
}

Color Color::operator+(const Color &other) {
  return add(*this,other);
}

Color Color::operator-(const Color &other) {
  return sub(*this,other);
}

Color Color::operator*(const Color &other) {
  return mul(*this,other);
}

Color Color::operator*(double lambda) {
  return scalar_mul(*this,lambda);
}

Color Color::clamp(){
  return clamp(*this);
}

double Color::r(){
  return color.x;
}

double Color::g(){
  return color.y;
}

double Color::b(){
  return color.z;
}
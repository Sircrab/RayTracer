//
// Created by Geno on 14-Oct-17.
//

#ifndef RAYTRACER_VEC2_H
#define RAYTRACER_VEC2_H
#include <string>
class Vec2{
public:
  double x,y;
  Vec2(double x, double y) : x(x),y(y){};
  Vec2() : x(0), y(0) {};
  static Vec2 add(const Vec2& a, const Vec2& b);
  static Vec2 sub(const Vec2& a, const Vec2& b);
  static Vec2 mul(const Vec2& a, const Vec2& b);
  static Vec2 div(const Vec2& a, const Vec2& b);
  static Vec2 scalar_mul(const Vec2& a, double b);
  static double dot(const Vec2& a, const Vec2& b);
  static double cross(const Vec2& a, const Vec2& b);
  Vec2 operator+(const Vec2& other) const;
  Vec2 operator-(const Vec2& other) const;
  Vec2 operator-() const;
  Vec2 operator*(const Vec2& other) const;
  Vec2 operator/(const Vec2& other) const;
  Vec2 operator*(double lambda) const;
  Vec2 operator+=(const Vec2& other);
  double operator[](const int idx) const;
  double magnitude() const;
  Vec2 normalize() const;
  double dot(const Vec2& other) const;
  double cross(const Vec2& other) const;
  std::string to_string() const;
};
#endif //RAYTRACER_VEC2_H

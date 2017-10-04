//
// Created by sircrab on 8/7/17.
//

#ifndef RAYTRACER_VEC3_H
#define RAYTRACER_VEC3_H
#include <string>
class Vec3{
public:
  double x,y,z;
  Vec3(double x, double y, double z) : x(x),y(y),z(z){};
  Vec3() : x(0), y(0), z(0) {};
  static Vec3 add(const Vec3& a, const Vec3& b);
  static Vec3 sub(const Vec3& a, const Vec3& b);
  static Vec3 mul(const Vec3& a, const Vec3& b);
  static Vec3 div(const Vec3& a, const Vec3& b);
  static Vec3 scalar_mul(const Vec3& a, double b);
  static double dot(const Vec3& a, const Vec3& b);
  static Vec3 cross(const Vec3& a, const Vec3& b);
  Vec3 operator+(const Vec3& other) const;
  Vec3 operator-(const Vec3& other) const;
  Vec3 operator-() const;
  Vec3 operator*(const Vec3& other) const;
  Vec3 operator/(const Vec3& other) const;
  Vec3 operator*(double lambda) const;
  Vec3 operator+=(const Vec3& other);
  double operator[](const int idx) const;
  double magnitude() const;
  Vec3 normalize() const;
  double dot(const Vec3& other) const;
  Vec3 cross(const Vec3& other) const;
  std::string to_string() const;
};

#endif //RAYTRACER_VEC3_H

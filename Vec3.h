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
    static Vec3 add(const Vec3& a, const Vec3& b);
    static Vec3 sub(const Vec3& a, const Vec3& b);
    static Vec3 mul(const Vec3& a, const Vec3& b);
    static Vec3 scalar_mul(const Vec3& a, double b);
    static double dot(const Vec3& a, const Vec3& b);
    static Vec3 cross(const Vec3& a, const Vec3& b);
    Vec3 operator+(const Vec3& other);
    Vec3 operator-(const Vec3& other);
    Vec3 operator-();
    Vec3 operator*(const Vec3& other);
    Vec3 operator*(double lambda);
    double magnitude();
    Vec3 normalize();
    double dot(const Vec3& other);
    Vec3 cross(const Vec3& other);
    std::string to_string();
};

#endif //RAYTRACER_VEC3_H

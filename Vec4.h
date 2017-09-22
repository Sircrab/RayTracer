//
// Created by sircrab on 8/11/17.
//

#ifndef RAYTRACER_VEC4_H
#define RAYTRACER_VEC4_H
#include <string>
class Vec4{
public:
    double x,y,z,w;
    Vec4(double x, double y, double z, double w) : x(x),y(y),z(z), w(w){};
    static Vec4 add(const Vec4& a, const Vec4& b);
    static Vec4 sub(const Vec4& a, const Vec4& b);
    static Vec4 mul(const Vec4& a, const Vec4& b);
    static Vec4 scalar_mul(const Vec4& a, double b);
    static double dot(const Vec4& a, const Vec4& b);
    Vec4 operator+(const Vec4& other);
    Vec4 operator-(const Vec4& other);
    Vec4 operator-();
    Vec4 operator*(const Vec4& other);
    Vec4 operator*(double lambda);
    double magnitude();
    Vec4 normalize();
    double dot(const Vec4& other);
    std::string to_string();
};
#endif //RAYTRACER_VEC4_H

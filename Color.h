//
// Created by Geno on 24-Aug-17.
//

#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H
#include <cmath>
#include "Vec3.h"
class Color{
public:
    Color();
    Color(double r, double g, double b);
    static Color clamp(const Color& other);
    static Color add(const Color& a, const Color& b);
    static Color sub(const Color& a, const Color& b);
    static Color mul(const Color& a, const Color& b);
    static Color scalar_mul(const Color& a, double lambda);
    Color operator+(const Color& other) const;
    Color operator-(const Color& other) const;
    Color operator*(const Color& other) const;
    Color operator*(double lambda) const;
    Color& operator+=(const Color&other);
    Color clamp();
    double r() const;
    double g() const;
    double b() const;
private:
    Vec3 color;
};
#endif //RAYTRACER_COLOR_H

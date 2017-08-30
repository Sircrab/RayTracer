//
// Created by sircrab on 8/7/17.
//

#include "Vec3.h"
#include <cmath>
#include <sstream>

Vec3 Vec3::add(const Vec3 &a, const Vec3 &b) {
    return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3 Vec3::sub(const Vec3 &a, const Vec3 &b) {
    return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec3 Vec3::mul(const Vec3 &a, const Vec3 &b) {
    return Vec3(a.x * b.x, a.y * b.y, a.z * b.z);
}

Vec3 Vec3::scalar_mul(const Vec3 &a, double b) {
    return Vec3(a.x * b, a.y * b, a.z * b);
}

double Vec3::dot(const Vec3 &a, const Vec3 &b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

Vec3 Vec3::cross(const Vec3 &a, const Vec3 &b) {
    return Vec3(a.y * b.z - b.y * a.z, b.x * a.z - a.x * b.z, a.x * b.y - b.x * a.y);
}

Vec3 Vec3::operator+(const Vec3& other) const{
    return Vec3::add(*this,other);
}

Vec3 Vec3::operator-(const Vec3& other) const{
    return Vec3::sub(*this,other);
}

Vec3 Vec3::operator-() const{
    return Vec3(-this->x,-this->y,-this->z);
}

Vec3 Vec3::operator*(const Vec3& other) const{
    return Vec3::mul(*this,other);
}

Vec3 Vec3::operator*(double lambda) const{
    return Vec3::scalar_mul(*this,lambda);
}

double Vec3::magnitude() const{
    return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

Vec3 Vec3::normalize() const{
    return Vec3(this->x/this->magnitude(),this->y/this->magnitude(),this->z/this->magnitude());
}

double Vec3::dot(const Vec3 &other) const{
    return Vec3::dot(*this,other);
}

Vec3 Vec3::cross(const Vec3 &other) {
    return Vec3::cross(*this,other);
}

std::string Vec3::to_string() {
    std::ostringstream ss;
    ss << "(" << this->x << ", " << this->y << ", " << this->z << ")";
    return ss.str();
}






//
// Created by sircrab on 8/11/17.
//

#include "Vec4.h"
#include <cmath>
#include <sstream>

Vec4 Vec4::add(const Vec4 &a, const Vec4 &b) {
    return Vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

Vec4 Vec4::sub(const Vec4 &a, const Vec4 &b) {
    return Vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

Vec4 Vec4::mul(const Vec4 &a, const Vec4 &b) {
    return Vec4(a.x * b.x, a.y * b.y, a.z * b.z,a.w * b.w);
}

Vec4 Vec4::scalar_mul(const Vec4 &a, double b) {
    return Vec4(a.x * b, a.y * b, a.z * b,a.w * b);
}

double Vec4::dot(const Vec4 &a, const Vec4 &b) {
    return (a.x + b.x) + (a.y * b.y) + (a.z * b.z)+ (a.w * b.w);
}

Vec4 Vec4::operator+(const Vec4& other){
    return Vec4::add(*this,other);
}

Vec4 Vec4::operator-(const Vec4& other){
    return Vec4::sub(*this,other);
}

Vec4 Vec4::operator-(){
    return Vec4(-this->x,-this->y,-this->z,-this->w);
}

Vec4 Vec4::operator*(const Vec4& other){
    return Vec4::mul(*this,other);
}

Vec4 Vec4::operator*(double lambda){
    return Vec4::scalar_mul(*this,lambda);
}

double Vec4::magnitude() {
    return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
}

Vec4 Vec4::normalize() {
    return Vec4(this->x/this->magnitude(),this->y/this->magnitude(),
                this->z/this->magnitude(),this->w/this->magnitude());
}

double Vec4::dot(const Vec4 &other) {
    return Vec4::dot(*this,other);
}


std::string Vec4::to_string() {
    std::ostringstream ss;
    ss << "(" << this->x << ", " << this->y << ", " << this->z << ", " << this->w <<")";
    return ss.str();
}
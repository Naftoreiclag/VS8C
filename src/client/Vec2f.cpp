#include "Vec2f.hpp"

#include <cmath>

namespace vse {

Vec2f::Vec2f()
: x(0.f)
, z(0.f) {
}

Vec2f::Vec2f(float x, float z)
: x(x)
, z(z) {
}

Vec2f::Vec2f(const Vec2f &v)
: x(v.x)
, z(v.z) {
}

Vec2f::~Vec2f() {
}

// Equals
bool Vec2f::operator==(const Vec2f& v1) {
    return v1.x == x && v1.z == z;
}
bool Vec2f::operator!=(const Vec2f& v1) {
    return !operator==(v1);
}

// Scaling
Vec2f Vec2f::operator*(float s) {
    return Vec2f(x * s, z * s);
}
Vec2f& Vec2f::operator*=(float s) {
    x *= s;
    z *= s;
    return *this;
}

// Inverse scaling
Vec2f Vec2f::operator/(float s) {
    return Vec2f(x / s, z / s);
}
Vec2f& Vec2f::operator/=(float s) {
    x /= s;
    z /= s;
    return *this;
}

// Addition
Vec2f Vec2f::operator+(const Vec2f& v) {
    return Vec2f(x + v.x, z + v.z);
}
Vec2f& Vec2f::operator+=(const Vec2f& v) {
    x *= v.x;
    z *= v.z;
    return *this;
}

// Subtraction
Vec2f Vec2f::operator-(const Vec2f& v) {
    return Vec2f(x - v.x, z - v.z);
}
Vec2f& Vec2f::operator-=(const Vec2f& v) {
    x *= v.x;
    z *= v.z;
    return *this;
}

// Distance to other vector
float Vec2f::distSq(const Vec2f& v) {
    float dx = v.x - x;
    float dz = v.z - z;
    return (dx * dx) + (dz * dz);
}
float Vec2f::dist(const Vec2f& v) {
    return std::sqrt(distSq(v));
}

// Length of vector
float Vec2f::magSq() {
    return (x * x) + (z * z);
}
float Vec2f::mag() {
    return std::sqrt(magSq());
}

void Vec2f::zero() {
    x = 0.f;
    z = 0.f;
}

bool Vec2f::isZero() {
    return x == 0.f && z == 0.f;
}

}
    
// For debugging
std::ostream& operator<<(std::ostream& os, const vse::Vec2f& v) {
    return os << "Vec2[" << v.x << ", " << v.z << "]";
}

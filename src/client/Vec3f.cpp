#include "Vec3f.hpp"

#include <cmath>
#include <math.h>

namespace vse {

Vec3f::Vec3f()
: x(0.f)
, y(0.f)
, z(0.f) {
}

Vec3f::Vec3f(float x, float y, float z)
: x(x)
, y(y)
, z(z) {
}

Vec3f::Vec3f(const Vec3f &v)
: x(v.x)
, y(v.y)
, z(v.z) {
}

Vec3f::~Vec3f() {
}

// Implicit conversions
Vec3f::operator Ogre::Vector3() const {
    return Ogre::Vector3(x, y, z);
}
Vec3f::Vec3f(const Ogre::Vector3& v)
: x(v.x)
, y(v.y)
, z(v.z) {
}
Vec3f::operator btVector3() const {
    return btVector3(x, y, z);
}
Vec3f::Vec3f(const btVector3& v)
: x(v.getX())
, y(v.getY())
, z(v.getZ()) {
}

// Equals
bool Vec3f::operator==(const Vec3f& v1) const {
    return v1.x == x && v1.y == y && v1.z == z;
}
bool Vec3f::operator!=(const Vec3f& v1) const {
    return !operator==(v1);
}

// Scaling
Vec3f Vec3f::operator*(float s) const {
    return Vec3f(x * s, y * s, z * s);
}
Vec3f& Vec3f::operator*=(float s) {
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

// Inverse scaling
Vec3f Vec3f::operator/(float s) const {
    return Vec3f(x / s, y / s, z / s);
}
Vec3f& Vec3f::operator/=(float s) {
    x /= s;
    y /= s;
    z /= s;
    return *this;
}

// Addition
Vec3f Vec3f::operator+(const Vec3f& v) const {
    return Vec3f(x + v.x, y + v.y, z + v.z);
}
Vec3f& Vec3f::operator+=(const Vec3f& v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

// Subtraction
Vec3f Vec3f::operator-(const Vec3f& v) const {
    return Vec3f(x - v.x, y - v.y, z - v.z);
}
Vec3f& Vec3f::operator-=(const Vec3f& v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

// Dot product
float Vec3f::dot(const Vec3f& v2) const {
    return (x * v2.x) + (y * v2.y) + (z * v2.z);
}

// Cross product
Vec3f Vec3f::cross(const Vec3f& v2) const {
    return Vec3f((y * v2.z) - (v2.y * z), (z * v2.x) - (v2.z * x), (x * v2.y) - (v2.x * y));
}

// Distance to other vector
float Vec3f::distSq(const Vec3f& v) const {
    float dx = v.x - x;
    float dy = v.y - y;
    float dz = v.z - z;
    return (dx * dx) + (dy * dy) + (dz * dz);
}
float Vec3f::dist(const Vec3f& v) const {
    return std::sqrt(distSq(v));
}

// Length of vector
float Vec3f::magSq() const {
    return (x * x) + (y * y) + (z * z);
}
float Vec3f::mag() const {
    return std::sqrt(magSq());
}

// Normalize this vector
void Vec3f::normalize() {
    float magnitude = mag();
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
}
// Normalized vector
Vec3f Vec3f::normalized() const {
    float magnitude = mag();
    return Vec3f(x / magnitude, y / magnitude, z / magnitude);
}

void Vec3f::zero() {
    x = 0.f;
    y = 0.f;
    z = 0.f;
}

bool Vec3f::isZero() const {
    return x == 0.f && y == 0.f && z == 0.f;
}
// isnan(x) || isnan(y) || isnan(z)
bool Vec3f::isNan() const {
    return std::isnan(x) || std::isnan(y) || std::isnan(z);
}

}
    
// For debugging
std::ostream& operator<<(std::ostream& os, const vse::Vec3f& v) {
    return os << "Vec3[" << v.x << ", " << v.y << ", " << v.z << "]";
}

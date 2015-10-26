#ifndef VEC3F_HPP
#define VEC3F_HPP

#include <ostream>

#include "btBulletDynamicsCommon.h"
#include "OgreVector3.h"

namespace vse {

class Vec3f {
public:
    float x;
    float y;
    float z;

    Vec3f();
    Vec3f(float x, float y, float z);
    ~Vec3f();
    
    // Copy constructor
    Vec3f(const Vec3f &v); 
    
    // Implicit conversions
    operator Ogre::Vector3() const;
    Vec3f(const Ogre::Vector3& v);
    operator btVector3() const;
    Vec3f(const btVector3& v);
    
    // Equals
    bool operator==(const Vec3f& v);
    bool operator!=(const Vec3f& v);
    
    // Scaling
    Vec3f operator*(float s);
    Vec3f& operator*=(float s);
    
    // Inverse scaling
    Vec3f operator/(float s);
    Vec3f& operator/=(float s);
    
    // Addition
    Vec3f operator+(const Vec3f& v);
    Vec3f& operator+=(const Vec3f& v);
    
    // Subtraction
    Vec3f operator-(const Vec3f& v);
    Vec3f& operator-=(const Vec3f& v);
    
    // Dot product
    float dot(const Vec3f& v1, const Vec3f& v2);
    
    // Cross product
    Vec3f cross(const Vec3f& v1, const Vec3f& v2);
    
    // Distance to other vector
    float dist(const Vec3f& v);
    float distSq(const Vec3f& v);
    
    // Length of vector
    float mag();
    float magSq();
    
    // Make zero
    void zero();
    
    // x == 0 && y == 0 && z == 0
    bool isZero();
};

}

// For debugging
std::ostream& operator<<(std::ostream& os, const vse::Vec3f& v);

#endif // VEC3F_HPP
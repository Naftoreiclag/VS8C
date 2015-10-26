#ifndef Vec2f_HPP
#define Vec2f_HPP

#include <ostream>

namespace vse {

class Vec2f {
public:
    float x;
    float z;

    Vec2f();
    Vec2f(float x, float z);
    Vec2f(const Vec2f &v); // Copy cstr
    ~Vec2f();
    
    // Equals
    bool operator==(const Vec2f& v);
    bool operator!=(const Vec2f& v);
    
    // Scaling
    Vec2f operator*(float s);
    Vec2f& operator*=(float s);
    
    // Inverse scaling
    Vec2f operator/(float s);
    Vec2f& operator/=(float s);
    
    // Addition
    Vec2f operator+(const Vec2f& v);
    Vec2f& operator+=(const Vec2f& v);
    
    // Subtraction
    Vec2f operator-(const Vec2f& v);
    Vec2f& operator-=(const Vec2f& v);
    
    // Distance to other vector
    float dist(const Vec2f& v);
    float distSq(const Vec2f& v);
    
    // Length of vector
    float mag();
    float magSq();
    
    // Make zero
    void zero();
    
    // x == 0 && z == 0
    bool isZero();
};

}

// For debugging
std::ostream& operator<<(std::ostream& os, const vse::Vec2f& v);

#endif // Vec2f_HPP

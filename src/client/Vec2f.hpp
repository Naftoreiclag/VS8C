/*
   Copyright 2015 James Fong

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

*/

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

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

#ifndef VSE_QUATE_HPP
#define VSE_QUATE_HPP

#include "btBulletDynamicsCommon.h"
#include "OgreQuaternion.h"

// Nothing but a way to easily convert between the many quaternion types

namespace vse {

class Quate {
public:
    float x;
    float y;
    float z;
    float w;

    Quate();
    Quate(float w, float x, float y, float z);
    ~Quate();
    
    // Copy-constructor
    Quate(const Quate& q);
    
    // Implicit conversions
    operator Ogre::Quaternion() const;
    Quate(const Ogre::Quaternion& q);
    operator btQuaternion() const;
    Quate(const btQuaternion& q);
};

}

#endif // VSE_QUATE_HPP

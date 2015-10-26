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

#include "Quate.hpp"

namespace vse {

Quate::Quate()
: w(0.f)
, x(0.f)
, y(0.f)
, z(0.f) {
}

Quate::Quate(float w, float x, float y, float z)
: w(w)
, x(x)
, y(y)
, z(z) {
}

Quate::~Quate() {}

// Copy-constructor
Quate::Quate(const Quate& q)
: w(q.w)
, x(q.x)
, y(q.y)
, z(q.z) {
}

// Implicit conversions
Quate::operator Ogre::Quaternion() const {
    return Ogre::Quaternion(w, x, y, z);
}
Quate::Quate(const Ogre::Quaternion& q)
: w(q.w)
, x(q.x)
, y(q.y)
, z(q.z) {
}
Quate::operator btQuaternion() const {
    // This kind of nonsense is exactly why I made this class
    return btQuaternion(x, y, z, w);
}
Quate::Quate(const btQuaternion& q)
: w(q.getW())
, x(q.getX())
, y(q.getY())
, z(q.getZ()) {
}

}


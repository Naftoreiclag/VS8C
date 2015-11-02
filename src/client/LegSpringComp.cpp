#include "LegSpringComp.hpp"

namespace vse {

const nres::ComponentID LegSpringComp::componentID = "sprleg";

LegSpringComp::LegSpringComp(
    const Vec3f& startOffset, 
    const Vec3f& endOffset, 
    const float& springStiffness,
    const float& springDamping,
    const float& footAccel,
    const float& footGrip,
    const float& maxUpVel,
    const float& minVelocityRelativeToGround,
    const Vec3f& upVector)
: mStart(startOffset)
, mEnd(endOffset)
, mLength(endOffset - startOffset)
, mDirection(mLength.normalized())
, mStiffness(springStiffness)
, mDamping(springDamping)
, mAccel(footAccel)
, mDecel(footGrip)
, mTouchingGround(false)
, mMaxUpwardVelLin(maxUpVel)
, mMinVelLin(minVelocityRelativeToGround)
, mUpVector(upVector) {
}

LegSpringComp::~LegSpringComp() {
}

const nres::ComponentID& LegSpringComp::getID() const {
    return componentID;
}


}


#include "LegSpringComp.hpp"

namespace vse
{

const nres::ComponentID LegSpringComp::componentID = "sprleg";

LegSpringComp::LegSpringComp(
    const Vec3f& startOffset, 
    const Vec3f& endOffset, 
    const float& springStiffness,
    const float& springDamping,
    const float& footAccel,
    const float& footGrip,
    const float& minVelocityRelativeToGround,
    const Vec3f& upVector)
: mStartOffset(startOffset)
, mEndOffset(endOffset)
, mSpring(endOffset - startOffset)
, mSpringNormalized(mSpring.normalized())
, mSpringStiffness(springStiffness)
, mSpringDamping(springDamping)
, mFootAccel(footAccel)
, mFootGrip(footGrip)
, mTouchingGround(false)
, mMinVelocityRelativeToGround(minVelocityRelativeToGround)
, mUpVector(upVector) {
}

LegSpringComp::~LegSpringComp() {
}

const nres::ComponentID& LegSpringComp::getID() const {
    return componentID;
}


}


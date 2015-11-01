#include "LegSpringComp.hpp"

namespace vse
{

const nres::ComponentID LegSpringComp::componentID = "sprleg";

LegSpringComp::LegSpringComp(const Vec3f& startOffset, const Vec3f& endOffset, const Vec3f& upVector)
: mStartOffset(startOffset)
, mEndOffset(endOffset)
, mUpVector(upVector) {
}

LegSpringComp::~LegSpringComp() {
}

const nres::ComponentID& LegSpringComp::getID() const {
    return componentID;
}


}


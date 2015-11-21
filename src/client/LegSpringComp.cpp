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


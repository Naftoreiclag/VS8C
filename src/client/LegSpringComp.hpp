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

#ifndef VSE_LEGSPRING_COMP
#define VSE_LEGSPRING_COMP

#include "btBulletDynamicsCommon.h"

#include "NRES.hpp"

#include "Vec3f.hpp"

namespace vse {

class LegSpringComp : public nres::Component {
public:
    // Spring properties
    Vec3f mLength;
    Vec3f mStart;
    Vec3f mEnd;
    Vec3f mDirection;
    float mStiffness;
    float mDamping;
    Vec3f mCompression;
    float mMaxUpwardVelLin; // Maximum upward velocity that can be achieved by the spring (aka no jumping to the moon); < 0 means no maximum
    
    float mTouchingGround; // If the spring is currently in contact with something
    const btRigidBody* mGroundBody; // Last body that was touched
    Vec3f mGroundVelLin; // Linear velocity of the last body that was touched
    
    Vec3f mTargetVelLin; // How fast we want to go
    float mMinVelLin; // The slowest we can go before speed is clamped to zero
    
    Vec3f mUpVector; // Opposes gravity
    
    bool mNeedStep; // If true, accelerate body to target velocity for one tick
    float mDecel; // Rate of deceleration when stopping
    float mAccel; // Rate of acceleration when moving
    
public:
    LegSpringComp(
        const Vec3f& start,
        const Vec3f& end,
        const float& stiffness,
        const float& damping,
        const float& accel,
        const float& decel,
        const float& maxUpVel = -1,
        const float& minVel = 0.3f,
        const Vec3f& upVector = Vec3f(0, 1, 0));
    ~LegSpringComp();
    
    static const nres::ComponentID componentID;
    const nres::ComponentID& getID() const;

};

}

#endif // VSE_LEGSPRING_COMP

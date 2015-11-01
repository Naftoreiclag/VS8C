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
        const float& minVel = 0.3f,
        const Vec3f& upVector = Vec3f(0, 1, 0));
    virtual ~LegSpringComp();
    
    static const nres::ComponentID componentID;
    virtual const nres::ComponentID& getID() const;

};

}

#endif // VSE_LEGSPRING_COMP

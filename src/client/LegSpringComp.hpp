#ifndef VSE_LEGSPRING_COMP
#define VSE_LEGSPRING_COMP

#include "btBulletDynamicsCommon.h"

#include "NRES.hpp"

#include "Vec3f.hpp"

namespace vse {

class LegSpringComp : public nres::Component {
public:
    Vec3f mLength;
    Vec3f mStart;
    Vec3f mEnd;
    Vec3f mDirection;
    float mStiffness;
    float mDamping;
    Vec3f mCompression;
    
    float mTouchingGround;
    const btRigidBody* mGroundBody;
    Vec3f mGroundVelocity;
    
    Vec3f mTargetVelLin;
    float mMinVelLin;
    
    Vec3f mUpVector;
    
    bool mNeedStep;
    float mDecel;
    float mAccel;
    
public:
    LegSpringComp(
        const Vec3f& startOffset,
        const Vec3f& endOffset,
        const float& springStiffness,
        const float& springDamping,
        const float& footAccel,
        const float& footGrip,
        const float& minVelocityRelativeToGround = 0.3f,
        const Vec3f& upVector = Vec3f(0, 1, 0));
    virtual ~LegSpringComp();
    
    static const nres::ComponentID componentID;
    virtual const nres::ComponentID& getID() const;

};

}

#endif // VSE_LEGSPRING_COMP

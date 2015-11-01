#ifndef VSE_LEGSPRING_COMP
#define VSE_LEGSPRING_COMP

#include "btBulletDynamicsCommon.h"

#include "NRES.hpp"

#include "Vec3f.hpp"

namespace vse {

class LegSpringComp : public nres::Component {
public:
    Vec3f mStartOffset;
    Vec3f mEndOffset;
    Vec3f mSpring;
    Vec3f mSpringNormalized;
    float mSpringStiffness;
    float mSpringDamping;
    Vec3f mSpringCompression;
    
    const btRigidBody* mGroundBody;
    Vec3f mGroundVelocity;
    
    
    bool mNeedStep;
    Vec3f mTargetVelocityRelativeToGround;
    float mMinVelocityRelativeToGround;
    
    Vec3f mUpVector;
    
    float mFootGrip;
    float mFootAccel;
    
    float mTouchingGround;
    
public:
    LegSpringComp(const Vec3f& startOffset, const Vec3f& endOffset, const Vec3f& upVector = Vec3f(0, 1, 0));
    virtual ~LegSpringComp();
    
    static const nres::ComponentID componentID;
    virtual const nres::ComponentID& getID() const;

};

}

#endif // VSE_LEGSPRING_COMP

#ifndef SKE_PHYSICSCOMP_HPP
#define SKE_PHYSICSCOMP_HPP

#include "btBulletDynamicsCommon.h"

#include "NRES.hpp"

#include "Quate.hpp"
#include "Vec3f.hpp"

namespace vse {

class RigidBodyComp : public nres::Component {
public:
    Quate mRotation;
    Vec3f mLocation;
    Vec3f mLinVel;
    bool mOnPhysUpdate;
    float mMass;
    
    Vec3f mInitialLoc;
    Vec3f mOffset;
public:
    static const nres::ComponentID componentID;
    RigidBodyComp(btCollisionShape* collisionShape, const Vec3f& initialPos = Vec3f(0, 0, 0), const Vec3f& bodyOffset = Vec3f(0, 0, 0));
    virtual ~RigidBodyComp();
    
    btCollisionShape* mCollisionShape; // For deletion
    btRigidBody* rigidBody;
    btMotionState* motionState;
public:
    virtual const nres::ComponentID& getID() const;

};

}

#endif // SKE_PHYSICSCOMP_HPP

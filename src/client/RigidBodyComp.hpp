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
    
    Vec3f mInitialPos;
    Vec3f mBodyOffset;
public:
    static const nres::ComponentID componentID;
    RigidBodyComp(btCollisionShape* collisionShape);
    virtual ~RigidBodyComp();
    
    btCollisionShape* mCollisionShape; // For deletion
    btRigidBody* rigidBody;
    btMotionState* motionState;
public:
    virtual const nres::ComponentID& getID() const;

};

}

#endif // SKE_PHYSICSCOMP_HPP

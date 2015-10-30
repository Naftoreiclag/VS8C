#ifndef SKE_PHYSICSCOMP_HPP
#define SKE_PHYSICSCOMP_HPP

#include "btBulletDynamicsCommon.h"

#include "NRES.hpp"

namespace vse {

class RigidBodyComp : public nres::Component {
public:
    btQuaternion mRotation;
    btVector3 mLocation;
    btVector3 mLinVel;
    bool mOnPhysUpdate;
public:
    static const nres::ComponentID componentID;
    RigidBodyComp(btCollisionShape* collisionShape);
    virtual ~RigidBodyComp();
    
    btCollisionShape* mCollisionShape; // For deletion
    btRigidBody* rigidBody;
    btMotionState* motionState;
public:
    virtual const nres::ComponentID& getID();

};

}

#endif // SKE_PHYSICSCOMP_HPP

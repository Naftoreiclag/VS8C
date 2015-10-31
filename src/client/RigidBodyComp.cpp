#include "RigidBodyComp.hpp"

namespace vse {

const nres::ComponentID RigidBodyComp::componentID = "physics";

RigidBodyComp::RigidBodyComp(btCollisionShape* collisionShape, const Vec3f& initialPos, const Vec3f& bodyOffset)
: mCollisionShape(collisionShape)
, mInitialPos(initialPos)
, mBodyOffset(bodyOffset) {
}

RigidBodyComp::~RigidBodyComp() {
    delete mCollisionShape;
    delete motionState;
    delete rigidBody;
}

const nres::ComponentID& RigidBodyComp::getID() const {
    return componentID;
}


}


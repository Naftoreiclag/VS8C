#include "RigidBodyComp.hpp"

namespace vse {

const nres::ComponentID RigidBodyComp::componentID = "physics";

RigidBodyComp::RigidBodyComp(btCollisionShape* collisionShape)
: mCollisionShape(collisionShape) {
}

RigidBodyComp::~RigidBodyComp() {
    delete mCollisionShape;
    delete motionState;
    delete rigidBody;
}

const nres::ComponentID& RigidBodyComp::getID() {
    return componentID;
}


}


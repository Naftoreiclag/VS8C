#include "PhysicsComp.hpp"

namespace vse {
    
const nres::ComponentID PhysicsComp::componentID = "box";

PhysicsComp::PhysicsComp(btCollisionShape* collisionShape)
: mCollisionShape(collisionShape) {
}

PhysicsComp::~PhysicsComp() {
    delete mCollisionShape;
    delete motionState;
    delete rigidBody;
}

const nres::ComponentID& PhysicsComp::getID() {
    return componentID;
}


}


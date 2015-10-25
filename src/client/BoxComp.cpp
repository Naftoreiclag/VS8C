#include "BoxComp.hpp"

namespace vse {
    
const nres::ComponentID BoxComp::componentID = "box";

BoxComp::BoxComp(btCollisionShape* collisionShape)
: mCollisionShape(collisionShape) {
    x = 0;
}

BoxComp::~BoxComp() {
    delete mCollisionShape;
    delete motionState;
    delete rigidBody;
}

const nres::ComponentID& BoxComp::getID() {
    return componentID;
}


}


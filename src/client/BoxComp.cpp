#include "BoxComp.hpp"

namespace vse {
    
const nres::ComponentID BoxComp::componentID = "box";

BoxComp::RigidBodyMotionListener::RigidBodyMotionListener(const btTransform& initialLoc, BoxComp* const sendTo)
: sendTo(sendTo),
initialLoc(initialLoc) {
}

void BoxComp::RigidBodyMotionListener::getWorldTransform(btTransform& worldTransform) const {
	worldTransform = initialLoc;
}

void BoxComp::RigidBodyMotionListener::setWorldTransform(const btTransform& worldTransform) {
	sendTo->rotation = worldTransform.getRotation();
	sendTo->location = worldTransform.getOrigin();
	sendTo->velocity = sendTo->rigidBody->getLinearVelocity();
	sendTo->needsAttencion = true;
}

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


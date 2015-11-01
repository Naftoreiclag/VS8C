#include "RigidBodyComp.hpp"

namespace vse {

const nres::ComponentID RigidBodyComp::componentID = "physics";

RigidBodyComp::RigidBodyComp(btCollisionShape* collisionShape, const float& mass, const Vec3f& initialPos, const Vec3f& bodyOffset)
: mCollisionShape(collisionShape)
, mMass(mass)
, mInitialLoc(initialPos)
, mOffset(bodyOffset) {
}

RigidBodyComp::~RigidBodyComp() {
    delete mCollisionShape;
    delete motionState;
    delete mRigidBody;
}

void RigidBodyComp::setAngularFactor(float factor) {
    mRigidBody->setAngularFactor(factor);
}
void RigidBodyComp::setAngularVelocity(Vec3f angVel) {
    mRigidBody->setAngularVelocity(angVel);
}
void RigidBodyComp::applyForce(Vec3f force, Vec3f relLoc) {
    mRigidBody->applyForce(force, relLoc);
}
void RigidBodyComp::applyImpulse(Vec3f impulse, Vec3f relLoc) {
    mRigidBody->applyImpulse(impulse, relLoc);
}

const nres::ComponentID& RigidBodyComp::getID() const {
    return componentID;
}


}


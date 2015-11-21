/*
   Copyright 2015 James Fong

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

*/

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
    delete mMotionState;
    delete mRigidBody;
}

void RigidBodyComp::setAngularFactor(float factor) {
    mRigidBody->setAngularFactor(factor);
}
void RigidBodyComp::setAngularVelocity(Vec3f angVel) {
    mRigidBody->setAngularVelocity(angVel);
}
void RigidBodyComp::applyForce(Vec3f force, Vec3f relLoc) {
    if(force.isZero()) {
        return;
    }
    mRigidBody->applyForce(force, relLoc);
}
void RigidBodyComp::applyImpulse(Vec3f impulse, Vec3f relLoc) {
    if(impulse.isZero()) {
        return;
    }
    mRigidBody->applyImpulse(impulse, relLoc);
}

const nres::ComponentID& RigidBodyComp::getID() const {
    return componentID;
}


}


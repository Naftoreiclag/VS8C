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

#include "RigidBodySys.hpp"

#include <algorithm>
#include <stdint.h>

#include "Overworld.hpp"
#include "RigidBodyComp.hpp"

#include "Vec3f.hpp"
#include "Quate.hpp"

#include "WalkSignal.hpp"
#include "LocationSignal.hpp"
#include "OrientationSignal.hpp"

namespace vse {

RigidBodySys::RigidBodyMotionListener::RigidBodyMotionListener(const btTransform& initialLoc, RigidBodyComp* const sendTo)
: sendTo(sendTo),
initialLoc(initialLoc) {
}

void RigidBodySys::RigidBodyMotionListener::getWorldTransform(btTransform& worldTransform) const {
    worldTransform = initialLoc;
}

void RigidBodySys::RigidBodyMotionListener::setWorldTransform(const btTransform& worldTransform) {
    sendTo->mRotation = worldTransform.getRotation();
    sendTo->mLocation = worldTransform.getOrigin() - sendTo->mOffset;
    sendTo->mVelocityLinear = sendTo->mRigidBody->getLinearVelocity();
    sendTo->mOnPhysUpdate = true;
}

RigidBodySys::RigidBodySys(btDynamicsWorld* dynamicsWorld)
: mDynamicsWorld(dynamicsWorld) {
    mRequiredComponents.push_back(RigidBodyComp::componentID);
}

RigidBodySys::~RigidBodySys() {
}

void RigidBodySys::onEntityExists(nres::Entity* entity) {
    RigidBodyComp* comp = (RigidBodyComp*) entity->getComponent(RigidBodyComp::componentID);
    
    btTransform trans;
    trans.setIdentity();
    trans.setOrigin(comp->mInitialLoc);
    comp->mMotionState = new RigidBodyMotionListener(trans, comp);
    btVector3 inertia(0, 0, 0);
    comp->mCollisionShape->calculateLocalInertia(comp->mMass, inertia);
    comp->mRigidBody = new btRigidBody(comp->mMass, comp->mMotionState, comp->mCollisionShape, inertia);
    comp->mRigidBody->setUserPointer(entity);
    mDynamicsWorld->addRigidBody(comp->mRigidBody);
    
    mTrackedEntities.push_back(entity);
}
void RigidBodySys::onEntityDestroyed(nres::Entity* entity) {
    RigidBodyComp* comp = (RigidBodyComp*) entity->getComponent(RigidBodyComp::componentID);
    
    mDynamicsWorld->removeRigidBody(comp->mRigidBody);
    
    mTrackedEntities.erase(std::remove(mTrackedEntities.begin(), mTrackedEntities.end(), entity), mTrackedEntities.end());
}
void RigidBodySys::onEntityBroadcast(nres::Entity* entity, const EntSignal* data) {
}
const std::vector<nres::ComponentID>& RigidBodySys::getRequiredComponents() {
    return mRequiredComponents;
}

void RigidBodySys::onTick() {
    for(std::vector<nres::Entity*>::iterator it = mTrackedEntities.begin(); it != mTrackedEntities.end(); ++ it) {
        nres::Entity* entity = *it;
        RigidBodyComp* rigidBody = (RigidBodyComp*) entity->getComponent(RigidBodyComp::componentID);
        
        if(rigidBody->mOnPhysUpdate) {
            entity->broadcast(new LocationSignal(Vec3f(rigidBody->mLocation)));
            entity->broadcast(new OrientationSignal(Quate(rigidBody->mRotation)));
            
            rigidBody->mOnPhysUpdate = false;
        }
    }
}
}


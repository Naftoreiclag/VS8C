#include "RigidBodySys.hpp"

#include <algorithm>
#include <stdint.h>

#include "VseApp.hpp"
#include "RigidBodyComp.hpp"

#include "Vec3f.hpp"
#include "Quate.hpp"

#include "LocalPlayerMoveSignal.hpp"
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
    sendTo->mLocation = worldTransform.getOrigin();
    sendTo->mLinVel = sendTo->rigidBody->getLinearVelocity();
    sendTo->mOnPhysUpdate = true;
}

RigidBodySys::RigidBodySys() {
    requiredComponents.push_back(RigidBodyComp::componentID);
    
    dynamicsWorld = VseApp::getSingleton().mDynamicsWorld;
}

RigidBodySys::~RigidBodySys() {
}

void RigidBodySys::onEntityExists(nres::Entity* entity) {
    RigidBodyComp* comp = (RigidBodyComp*) entity->getComponent(RigidBodyComp::componentID);
    
    btScalar mass = 1;
    btTransform trans;
    trans.setIdentity();
    trans.setOrigin(btVector3(4, 5, 4));
    comp->motionState = new RigidBodyMotionListener(trans, comp);
    btVector3 inertia(0, 0, 0);
    comp->mCollisionShape->calculateLocalInertia(mass, inertia);
    comp->rigidBody = new btRigidBody(mass, comp->motionState, comp->mCollisionShape, inertia);
    dynamicsWorld->addRigidBody(comp->rigidBody);
    
    trackedEntities.push_back(entity);
}
void RigidBodySys::onEntityDestroyed(nres::Entity* entity) {
    trackedEntities.erase(std::remove(trackedEntities.begin(), trackedEntities.end(), entity), trackedEntities.end());
}
void RigidBodySys::onEntityBroadcast(nres::Entity* entity, const EntSignal* data) {
    switch(data->getType()) {
        case EntSignal::Type::LOCAL_PLAYER_MOVE: {
            LocalPlayerMoveSignal* signal = (LocalPlayerMoveSignal*) data;
            
            RigidBodyComp* comp = (RigidBodyComp*) entity->getComponent(RigidBodyComp::componentID);
            comp->rigidBody->applyCentralForce(signal->requestedMovement);
            break;
        }
        default: {
            break;
        }
    }
}
const std::vector<nres::ComponentID>& RigidBodySys::getRequiredComponents() {
    return requiredComponents;
}

void RigidBodySys::onTick(float tps) {
    for(std::vector<nres::Entity*>::iterator it = trackedEntities.begin(); it != trackedEntities.end(); ++ it) {
        nres::Entity* entity = *it;
        RigidBodyComp* comp = (RigidBodyComp*) entity->getComponent(RigidBodyComp::componentID);
        
        if(comp->mOnPhysUpdate) {
            entity->broadcast(new LocationSignal(Vec3f(comp->mLocation)));
            entity->broadcast(new OrientationSignal(Quate(comp->mRotation)));
            
            comp->mOnPhysUpdate = false;
        }
    }
}
}


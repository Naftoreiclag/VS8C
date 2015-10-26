#include "PhysicsSys.hpp"

#include <stdint.h>

#include "VseApp.hpp"
#include "PhysicsComp.hpp"

#include "Vec3f.hpp"
#include "Quate.hpp"

#include "LocalPlayerMoveSignal.hpp"
#include "LocationSignal.hpp"
#include "OrientationSignal.hpp"

namespace vse {

PhysicsSys::RigidBodyMotionListener::RigidBodyMotionListener(const btTransform& initialLoc, PhysicsComp* const sendTo)
: sendTo(sendTo),
initialLoc(initialLoc) {
}

void PhysicsSys::RigidBodyMotionListener::getWorldTransform(btTransform& worldTransform) const {
    worldTransform = initialLoc;
}

void PhysicsSys::RigidBodyMotionListener::setWorldTransform(const btTransform& worldTransform) {
    sendTo->mRotation = worldTransform.getRotation();
    sendTo->mLocation = worldTransform.getOrigin();
    sendTo->mLinVel = sendTo->rigidBody->getLinearVelocity();
    sendTo->mOnPhysUpdate = true;
}

PhysicsSys::PhysicsSys() {
    requiredComponents.push_back(PhysicsComp::componentID);
    
    dynamicsWorld = VseApp::getSingleton().mDynamicsWorld;
}

PhysicsSys::~PhysicsSys() {
}

void PhysicsSys::onEntityExists(nres::Entity* entity) {
    PhysicsComp* comp = (PhysicsComp*) entity->getComponent(PhysicsComp::componentID);
    
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
void PhysicsSys::onEntityDestroyed(nres::Entity* entity) {
    
}
void PhysicsSys::onEntityBroadcast(nres::Entity* entity, const EntSignal* data) {
    switch(data->getType()) {
        case EntSignal::Type::LOCAL_PLAYER_MOVE: {
            LocalPlayerMoveSignal* signal = (LocalPlayerMoveSignal*) data;
            
            PhysicsComp* comp = (PhysicsComp*) entity->getComponent(PhysicsComp::componentID);
            comp->rigidBody->applyCentralForce(signal->requestedMovement);
            break;
        }
        default: {
            break;
        }
    }
}
const std::vector<nres::ComponentID>& PhysicsSys::getRequiredComponents() {
    return requiredComponents;
}

void PhysicsSys::onTick(float tps) {
    for(std::vector<nres::Entity*>::iterator it = trackedEntities.begin(); it != trackedEntities.end(); ++ it) {
        nres::Entity* entity = *it;
        PhysicsComp* comp = (PhysicsComp*) entity->getComponent(PhysicsComp::componentID);
        
        if(comp->mOnPhysUpdate) {
            entity->broadcast(new LocationSignal(Vec3f(comp->mLocation)));
            entity->broadcast(new OrientationSignal(Quate(comp->mRotation)));
            
            comp->mOnPhysUpdate = false;
        }
    }
}
}


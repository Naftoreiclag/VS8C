#include "PhysicsSys.hpp"

#include <sstream>
#include <stdint.h>

#include "VseApp.hpp"
#include "PhysicsComp.hpp"

#include "Vec3f.hpp"
#include "Quate.hpp"

#include "LocalPlayerMoveSignal.hpp"

namespace vse {


BoxSys::RigidBodyMotionListener::RigidBodyMotionListener(const btTransform& initialLoc, PhysicsComp* const sendTo)
: sendTo(sendTo),
initialLoc(initialLoc) {
}

void BoxSys::RigidBodyMotionListener::getWorldTransform(btTransform& worldTransform) const {
	worldTransform = initialLoc;
}

void BoxSys::RigidBodyMotionListener::setWorldTransform(const btTransform& worldTransform) {
	sendTo->mRotation = worldTransform.getRotation();
	sendTo->mLocation = worldTransform.getOrigin();
	sendTo->mLinVel = sendTo->rigidBody->getLinearVelocity();
	sendTo->mOnPhysUpdate = true;
}
    
std::string BoxSys::generateOgreEntityName() {
    static uint32_t id = 0;
    
    std::stringstream ss;
    ss << "cube" << id;
    
    ++ id;
    return ss.str();
}

BoxSys::BoxSys() {
    requiredComponents.push_back(PhysicsComp::componentID);
    
    dynamicsWorld = VseApp::getSingleton().mDynamicsWorld;
    smgr = VseApp::getSingleton().mSmgr;
}

BoxSys::~BoxSys() {
}

void BoxSys::onEntityExists(nres::Entity* entity) {
    PhysicsComp* comp = (PhysicsComp*) entity->getComponent(PhysicsComp::componentID);
    comp->boxNode = smgr->getRootSceneNode()->createChildSceneNode();
    comp->boxModel = smgr->createEntity(generateOgreEntityName(), "Cube.mesh");
    comp->boxNode->attachObject(comp->boxModel);
    
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
void BoxSys::onEntityDestroyed(nres::Entity* entity) {
    
}
void BoxSys::onEntityBroadcast(nres::Entity* entity, const EntSignal* data) {
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
const std::vector<nres::ComponentID>& BoxSys::getRequiredComponents() {
    return requiredComponents;
}

void BoxSys::onTick(float tps) {
    for(std::vector<nres::Entity*>::iterator it = trackedEntities.begin(); it != trackedEntities.end(); ++ it) {
        nres::Entity* entity = *it;
        PhysicsComp* comp = (PhysicsComp*) entity->getComponent(PhysicsComp::componentID);
        
        if(comp->mOnPhysUpdate) {
            comp->boxNode->setPosition(Vec3f(comp->mLocation));
            comp->boxNode->setOrientation(Quate(comp->mRotation));
            
            comp->mOnPhysUpdate = false;
        }
        
    }
}
}


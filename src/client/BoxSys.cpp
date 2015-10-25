#include "BoxSys.hpp"

#include "VseApp.hpp"
#include "BoxComp.hpp"

#include <sstream>
#include <stdint.h>

namespace vse
{
    
std::string BoxSys::generateOgreEntityName() {
    static uint32_t id = 0;
    
    std::stringstream ss;
    ss << "cube" << id;
    
    ++ id;
    return ss.str();
    
}

BoxSys::BoxSys() {
    requiredComponents.push_back(BoxComp::componentID);
    
    dynamicsWorld = VseApp::getSingleton().mDynamicsWorld;
    smgr = VseApp::getSingleton().mSmgr;
}

BoxSys::~BoxSys()
{
}

void BoxSys::onEntityExists(nres::Entity* entity) {
    BoxComp* comp = (BoxComp*) entity->getComponent(BoxComp::componentID);
    comp->boxNode = smgr->getRootSceneNode()->createChildSceneNode();
    comp->boxModel = smgr->createEntity(generateOgreEntityName(), "Cube.mesh");
    comp->boxNode->attachObject(comp->boxModel);
    
    btScalar mass = 1;
    btTransform trans;
    trans.setIdentity();
    trans.setOrigin(btVector3(4, 5, 4));
    comp->motionState = new BoxComp::RigidBodyMotionListener(trans, comp);
    btVector3 inertia(0, 0, 0);
    comp->mCollisionShape->calculateLocalInertia(mass, inertia);
    comp->rigidBody = new btRigidBody(mass, comp->motionState, comp->mCollisionShape, inertia);
    dynamicsWorld->addRigidBody(comp->rigidBody);
    
    trackedEntities.push_back(entity);
}
void BoxSys::onEntityDestroyed(nres::Entity* entity) {
    
}
void BoxSys::onEntityBroadcast(nres::Entity* entity, void* data) {
    
}
const std::vector<nres::ComponentID>& BoxSys::getRequiredComponents() {
    return requiredComponents;
}


void BoxSys::onTick(float tps) {
    for(std::vector<nres::Entity*>::iterator it = trackedEntities.begin(); it != trackedEntities.end(); ++ it) {
        nres::Entity* entity = *it;
        BoxComp* comp = (BoxComp*) entity->getComponent(BoxComp::componentID);
        
        comp->x += tps;
        
        if(comp->needsAttencion) {
            comp->boxNode->setPosition(comp->location.getX(), comp->location.getY(), comp->location.getZ());
            comp->boxNode->setOrientation(comp->rotation.getW(), comp->rotation.getX(), comp->rotation.getY(), comp->rotation.getZ());
            
            needsAttencion = false;
        }
        
    }
}
}


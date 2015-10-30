#include "LegSpringSys.hpp"

#include <algorithm>

#include "RigidBodyComp.hpp"
#include "LegSpringComp.hpp"

namespace vse
{

LegSpringSys::LegSpringSys(btDiscreteDynamicsWorld* const dynamicsWorld)
: mDynamicsWorld(dynamicsWorld) {
    mRequiredComponents.push_back(LegSpringComp::componentID);
    mRequiredComponents.push_back(RigidBodyComp::componentID);
}

LegSpringSys::~LegSpringSys() {
}


void LegSpringSys::onEntityExists(nres::Entity* entity) {
    mTrackedEntities.push_back(entity);
}
void LegSpringSys::onEntityDestroyed(nres::Entity* entity) {
    mTrackedEntities.erase(std::remove(mTrackedEntities.begin(), mTrackedEntities.end(), entity), mTrackedEntities.end());
}
void LegSpringSys::onEntityBroadcast(nres::Entity* entity, const EntSignal* data) {
    
}

const std::vector<nres::ComponentID>& LegSpringSys::getRequiredComponents() {
    return mRequiredComponents;
}

void LegSpringSys::onTick(float tps) {
    for(std::vector<nres::Entity*>::iterator it = mTrackedEntities.begin(); it != mTrackedEntities.end(); ++ it) {
        nres::Entity* entity = *it;
        LegSpringComp* legSpring = (LegSpringComp*) entity->getComponent(LegSpringComp::componentID);
        RigidBodyComp* rigidBody = (RigidBodyComp*) entity->getComponent(RigidBodyComp::componentID);
        
        
        
        
        
    }
}

}


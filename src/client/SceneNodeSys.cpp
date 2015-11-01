#include "SceneNodeSys.hpp"

#include <algorithm>
#include <sstream>
#include <stdint.h>

#include "VseApp.hpp"
#include "RigidBodyComp.hpp"

#include "Vec3f.hpp"
#include "Quate.hpp"

#include "LocationSignal.hpp"
#include "OrientationSignal.hpp"

namespace vse {
    
std::string SceneNodeSys::generateOgreEntityName() {
    static uint32_t id = 0;
    
    std::stringstream ss;
    ss << "vse" << id;
    
    ++ id;
    return ss.str();
}

SceneNodeSys::SceneNodeSys(Ogre::SceneManager* smgr)
: mSmgr(smgr) {
    mRequiredComponents.push_back(SceneNodeComp::componentID);
}

SceneNodeSys::~SceneNodeSys() {
}

void SceneNodeSys::onEntityExists(nres::Entity* entity) {
    SceneNodeComp* comp = (SceneNodeComp*) entity->getComponent(SceneNodeComp::componentID);
    comp->boxNode = mSmgr->getRootSceneNode()->createChildSceneNode();
    comp->boxModel = mSmgr->createEntity(generateOgreEntityName(), "Cube.mesh");
    comp->boxNode->attachObject(comp->boxModel);
    
    mTrackedEntities.push_back(entity);
}
void SceneNodeSys::onEntityDestroyed(nres::Entity* entity) {
    mTrackedEntities.erase(std::remove(mTrackedEntities.begin(), mTrackedEntities.end(), entity), mTrackedEntities.end());
}
void SceneNodeSys::onEntityBroadcast(nres::Entity* entity, const EntSignal* data) {
    switch(data->getType()) {
        case EntSignal::Type::LOCATION: {
            LocationSignal* signal = (LocationSignal*) data;
            SceneNodeComp* comp = (SceneNodeComp*) entity->getComponent(SceneNodeComp::componentID);
            comp->boxNode->setPosition(signal->mLocationUpdate);
            
            break;
        }
        case EntSignal::Type::ORIENTATION: {
            OrientationSignal* signal = (OrientationSignal*) data;
            SceneNodeComp* comp = (SceneNodeComp*) entity->getComponent(SceneNodeComp::componentID);
            comp->boxNode->setOrientation(signal->mOrientationUpdate);
            
            break;
        }
        default: {
            break;
        }
    }
}
const std::vector<nres::ComponentID>& SceneNodeSys::getRequiredComponents() {
    return mRequiredComponents;
}

}
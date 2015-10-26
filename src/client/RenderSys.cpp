#include "RenderSys.hpp"

#include <sstream>
#include <stdint.h>

#include "VseApp.hpp"
#include "PhysicsComp.hpp"

#include "Vec3f.hpp"
#include "Quate.hpp"

#include "LocationSignal.hpp"
#include "OrientationSignal.hpp"

namespace vse {
    
std::string RenderSys::generateOgreEntityName() {
    static uint32_t id = 0;
    
    std::stringstream ss;
    ss << "cube" << id;
    
    ++ id;
    return ss.str();
}

RenderSys::RenderSys() {
    requiredComponents.push_back(SceneNodeComp::componentID);
    
    smgr = VseApp::getSingleton().mSmgr;
}

RenderSys::~RenderSys() {
}

void RenderSys::onEntityExists(nres::Entity* entity) {
    SceneNodeComp* comp = (SceneNodeComp*) entity->getComponent(SceneNodeComp::componentID);
    comp->boxNode = smgr->getRootSceneNode()->createChildSceneNode();
    comp->boxModel = smgr->createEntity(generateOgreEntityName(), "Cube.mesh");
    comp->boxNode->attachObject(comp->boxModel);
    
    trackedEntities.push_back(entity);
}
void RenderSys::onEntityDestroyed(nres::Entity* entity) {
    
}
void RenderSys::onEntityBroadcast(nres::Entity* entity, const EntSignal* data) {
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
const std::vector<nres::ComponentID>& RenderSys::getRequiredComponents() {
    return requiredComponents;
}

}
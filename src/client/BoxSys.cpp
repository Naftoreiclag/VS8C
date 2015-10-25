#include "BoxSys.hpp"

#include "BoxComp.hpp"

namespace vse
{

BoxSys::BoxSys() {
    requiredComponents.push_back(BoxComp::staticID);
}

BoxSys::~BoxSys()
{
}

void BoxSys::entityExists(nres::Entity* entity) {
    trackedEntities.push_back(entity);
}
void BoxSys::entityDestroyed(nres::Entity* entity) {
    
}
void BoxSys::entityBroadcasted(nres::Entity* entity, void* data) {
    
}
const std::vector<nres::ComponentID>& BoxSys::getRequiredComponents() {
    return requiredComponents;
}


void BoxSys::tick(float tps) {
    for(std::vector<nres::Entity*>::iterator it = trackedEntities.begin(); it != trackedEntities.end(); ++ it) {
        nres::Entity* entity = *it;
        BoxComp* comp = (BoxComp*) entity->getComponent(BoxComp::staticID);
        
        comp->x += tps;
    }
}
}


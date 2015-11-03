#include "SerializationUtil.hpp"

#include <stdint.h>
#include <vector>

namespace vse {

namespace SerializationUtil {

void serializeEntities(const nres::World& world, Json::Value& jsonRoot) {
    
    uint32_t entityIndex = 0;
    const std::vector<nres::Entity*>& entities = world.getEntities();
    for(std::vector<nres::Entity*>::const_iterator entIter = entities.begin(); entIter != entities.end(); ++ entIter) {
        const nres::Entity* entity = *entIter;
        
        Json::Value& jsonEntity = jsonRoot[entityIndex];
        
        uint32_t componentIndex = 0;
        const std::vector<nres::Component*>& components = entity->getComponents();
        for(std::vector<nres::Component*>::const_iterator compIter = components.begin(); compIter != components.end(); ++ entIter) {
            const nres::Component* component = *compIter;
            
            Json::Value& jsonComponent = jsonEntity[component->getID()];
            
            // ???
            
            ++ componentIndex;
        }
        
        ++ entityIndex;
    }
}

void deserializeEntities(nres::World& world, const Json::Value& json) {
    
}

}

}


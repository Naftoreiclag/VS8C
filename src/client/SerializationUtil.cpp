#include "SerializationUtil.hpp"

#include <vector>

namespace vse {

namespace SerializationUtil {

void serializeEntities(const nres::World& world, Json::Value& json) {
    const std::vector<nres::Entity*>& entities = world.getEntities();
    
    for(std::vector<nres::Entity*>::const_iterator entIter = entities.begin(); entIter != entities.end(); ++ entIter) {
    }
}

void deserializeEntities(nres::World& world, const Json::Value& json) {
    
}

}

}


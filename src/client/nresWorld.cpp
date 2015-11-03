#include "nresWorld.hpp"

#include <algorithm>

namespace nres {

World::World() {
}

World::~World() {
}

void World::attachSystem(System* system) {
    systems.push_back(system);
}

Entity* World::newEntity() {
    Entity* ret = new Entity(this);
    
    entities.push_back(ret);
    
    return ret;
}

void World::deleteEntity(Entity* entity) {
    entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
    
    delete entity;
}

void World::deleteAllEntities() {
    for(std::vector<Entity*>::iterator entIter = entities.begin(); entIter != entities.end(); ++ entIter) {
        Entity* entity = *entIter;
        
        delete entity;
    }
    
    entities.clear();
}

const std::vector<Entity*>& World::getEntities() const {
    return entities;
}

}


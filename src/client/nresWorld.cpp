#include "nresWorld.hpp"

namespace nres
{

World::World()
{
}

World::~World()
{
}

void World::attachSystem(System* system) {
    systems.push_back(system);
}

Entity* World::newEntity() {
    return new Entity(this);
}

void World::deleteEntity(Entity* entity) {
    delete entity;
}


}


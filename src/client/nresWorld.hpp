#ifndef NRES_WORLD_HPP
#define NRES_WORLD_HPP

#include <vector>

#include "nresSystem.hpp"
#include "nresEntity.hpp"

namespace nres
{

class World {
public:
    World();
    ~World();
private:
    std::vector<System*> systems;
    std::vector<Entity*> entities;

public:
    void attachSystem(System* system);
    
    Entity* newEntity();
    void deleteEntity(Entity* entity);
    void deleteAllEntities();
    
    const std::vector<Entity*>& getEntities() const;
    
    friend class Entity;
};

}

#endif // NRES_WORLD_HPP

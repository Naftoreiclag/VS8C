#ifndef NRES_ENTITY_HPP
#define NRES_ENTITY_HPP

#include <vector>

#include "nresTypedefs.hpp"

#include "EntSignal.hpp"

namespace nres
{
    
class World;
class Component;
class System;

class Entity {
public:
    Entity(World* world);
    ~Entity();
private:
    World* const world;
    
    std::vector<Component*> components;
    std::vector<System*> systems;
    
    bool isPublished;
    
public:
    void add(Component* component);
    void publish();
    
    Component* getComponent(const ComponentID& componentID);
    
    void broadcast(vse::EntSignal* data);
};

}

#endif // NRES_ENTITY_HPP

#ifndef NRES_ENTITY_HPP
#define NRES_ENTITY_HPP

#include <vector>

#include "nresListener.hpp"
#include "nresTypedefs.hpp"

#include "EntSignal.hpp"

namespace nres {
    
class World;
class Component;
class System;

class Entity {
public:
    Entity(World* world);
    ~Entity();
private:
    World* const world;
    
    std::vector<Listener*> listeners;
    std::vector<Component*> components;
    
    bool isPublished;
    
public:
    void add(Component* component);
    void addListener(Listener* listener);
    void publish();
    void destroy();
    
    Component* getComponent(const ComponentID& componentID);
    
    void broadcast(vse::EntSignal* data);
    
    const std::vector<Component*>& getComponents() const;
};

}

#endif // NRES_ENTITY_HPP

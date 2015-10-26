#include "nresEntity.hpp"

#include <iostream>
#include <cassert>

#include "nresWorld.hpp"
#include "nresComponent.hpp"

namespace nres
{

Entity::Entity(World* world)
: world(world)
, isPublished(false) {
}

Entity::~Entity()
{
}


void Entity::add(Component* component) {
    assert(!isPublished);
    
    components.push_back(component);
}

void Entity::publish() {
    assert(!isPublished);
    isPublished = true;
    
    // Try find which systems correspond with this entity's set of components
    
    // Iterate over every system
    for(std::vector<System*>::iterator sysIter = world->systems.begin(); sysIter != world->systems.end(); ++ sysIter) {
        System* sys = *sysIter;
        
        // Iterate over that system's requirements, check that each one is fulfilled
        bool haveAllRequirements = true;
        const std::vector<ComponentID>& requirements = sys->getRequiredComponents();
        for(std::vector<ComponentID>::const_iterator reqIter = requirements.begin(); reqIter != requirements.end(); ++ reqIter) {
            const ComponentID& reqId = *reqIter;
            
            // Check if we fulfill this requirements
            bool haveRequirement = false;
            for(std::vector<Component*>::iterator compIter = components.begin(); compIter != components.end(); ++ compIter) {
                Component* myComponent = *compIter;
                
                if(myComponent->getID() == reqId) {
                    haveRequirement = true;
                    break;
                }
            }
            
            // If we are missing a single requirement, then we do not have all of them
            if(!haveRequirement) {
                haveAllRequirements = false;
                break;
            }
        }
        
        // Entity has all requirements, therefore tell it that we exist
        if(haveAllRequirements) {
            systems.push_back(sys);
            sys->onEntityExists(this);
        }
    }
}

Component* Entity::getComponent(const ComponentID& componentID) {
    assert(isPublished);
    
    for(std::vector<Component*>::iterator compIter = components.begin(); compIter != components.end(); ++ compIter) {
        Component* comp = *compIter;
        
        if(comp->getID() == componentID) {
            return comp;
        }
    }
    
    return 0;
}

void Entity::broadcast(vse::EntSignal* data) {
    assert(isPublished);
    
    for(std::vector<System*>::iterator sysIter = systems.begin(); sysIter != systems.end(); ++ sysIter) {
        System* sys = *sysIter;
        
        sys->onEntityBroadcast(this, data);
    }
    
    delete data;
}

}


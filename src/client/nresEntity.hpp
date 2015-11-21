/*
   Copyright 2015 James Fong

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

*/

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

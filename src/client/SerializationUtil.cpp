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

#include "SerializationUtil.hpp"

#include <stdint.h>
#include <vector>

#include "SceneNodeComp.hpp"
#include "RigidBodyComp.hpp"
#include "LegSpringComp.hpp"
#include "LocalPlayerComp.hpp"

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
        for(std::vector<nres::Component*>::const_iterator compIter = components.begin(); compIter != components.end(); ++ compIter) {
            const nres::Component* component = *compIter;
            
            Json::Value& jsonComponent = jsonEntity[component->getID()];
            
            if(component->getID() == SceneNodeComp::componentID) {
                const SceneNodeComp* sceneNode = static_cast<const SceneNodeComp*>(component);
                
                jsonComponent["resourceName"] = sceneNode->mResourceName;
            }
            else if(component->getID() == RigidBodyComp::componentID) {
                const RigidBodyComp* rigidBody = static_cast<const RigidBodyComp*>(component);
                
                serialize(rigidBody->mLocation, jsonComponent["location"]);
                serialize(rigidBody->mRotation, jsonComponent["rotation"]);
                jsonComponent["mass"] = rigidBody->mMass;
            }
            else {
                
            }
            
            ++ componentIndex;
        }
        
        ++ entityIndex;
    }
}

void deserializeEntities(nres::World& world, const Json::Value& json) {
    
}
    
void serializeComponent(const nres::Component& component, Json::Value& json) {
    if(component.getID() == SceneNodeComp::componentID) {
        
    }
}

nres::Component* deserializeComponent(nres::ComponentID id, const Json::Value& json) {
    
}
void serialize(const Vec3f& vector, Json::Value& json) {
    json["x"] = vector.x;
    json["y"] = vector.y;
    json["z"] = vector.z;
}
void serialize(const Quate& quater, Json::Value& json) {
    json["w"] = quater.w;
    json["x"] = quater.x;
    json["y"] = quater.y;
    json["z"] = quater.z;
}

}

}


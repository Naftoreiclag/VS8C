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

#include "SceneNodeSys.hpp"

#include <algorithm>
#include <sstream>
#include <stdint.h>

#include "OgreStringVector.h"

#include "AnimateSignal.hpp"
#include "LocationSignal.hpp"
#include "OrientationSignal.hpp"
#include "Overworld.hpp"
#include "Quate.hpp"
#include "RigidBodyComp.hpp"
#include "Vec3f.hpp"

namespace vse {
    
std::string SceneNodeSys::generateOgreEntityName() {
    static uint32_t id = 0;
    
    std::stringstream ss;
    ss << "vse" << id;
    
    ++ id;
    return ss.str();
}

SceneNodeSys::SceneNodeSys(Ogre::SceneManager* smgr)
: mSmgr(smgr) {
    mRequiredComponents.push_back(SceneNodeComp::componentID);
}

SceneNodeSys::~SceneNodeSys() {
}

void SceneNodeSys::onEntityExists(nres::Entity* entity) {
    SceneNodeComp* sceneNode = (SceneNodeComp*) entity->getComponent(SceneNodeComp::componentID);
    sceneNode->mSceneNode = mSmgr->getRootSceneNode()->createChildSceneNode();
    sceneNode->mOgreEntity = mSmgr->createEntity(generateOgreEntityName(), sceneNode->mResourceName);
    sceneNode->mSceneNode->attachObject(sceneNode->mOgreEntity);
    
    mTrackedEntities.push_back(entity);
}
void SceneNodeSys::onEntityDestroyed(nres::Entity* entity) {
    SceneNodeComp* sceneNode = (SceneNodeComp*) entity->getComponent(SceneNodeComp::componentID);
    
    mSmgr->destroySceneNode(sceneNode->mSceneNode);
    mSmgr->destroyEntity(sceneNode->mOgreEntity);
    
    mTrackedEntities.erase(std::remove(mTrackedEntities.begin(), mTrackedEntities.end(), entity), mTrackedEntities.end());
}
void SceneNodeSys::onEntityBroadcast(nres::Entity* entity, const EntSignal* data) {
    switch(data->getType()) {
        case EntSignal::Type::ANIMATION: {
            AnimateSignal* signal = (AnimateSignal*) data;
            SceneNodeComp* comp = (SceneNodeComp*) entity->getComponent(SceneNodeComp::componentID);
            
            comp->mAnimState = comp->mOgreEntity->getAnimationState(signal->mAnimName);
            
            if(comp->mAnimState) {
                comp->mAnimState->setLoop(true);
                comp->mAnimState->setEnabled(true);
            }
        }
        case EntSignal::Type::LOCATION: {
            LocationSignal* signal = (LocationSignal*) data;
            SceneNodeComp* comp = (SceneNodeComp*) entity->getComponent(SceneNodeComp::componentID);
            comp->mSceneNode->setPosition(signal->mLocationUpdate + comp->mSceneNodeOffset);
            
            break;
        }
        case EntSignal::Type::ORIENTATION: {
            OrientationSignal* signal = (OrientationSignal*) data;
            SceneNodeComp* comp = (SceneNodeComp*) entity->getComponent(SceneNodeComp::componentID);
            comp->mSceneNode->setOrientation(signal->mOrientationUpdate);
            
            break;
        }
        default: {
            break;
        }
    }
}
const std::vector<nres::ComponentID>& SceneNodeSys::getRequiredComponents() {
    return mRequiredComponents;
}

void SceneNodeSys::onTick(const float& tps) {
    for(std::vector<nres::Entity*>::iterator it = mTrackedEntities.begin(); it != mTrackedEntities.end(); ++ it) {
        nres::Entity* entity = *it;
        
        SceneNodeComp* comp = (SceneNodeComp*) entity->getComponent(SceneNodeComp::componentID);
        if(comp->mAnimState) {
            comp->mAnimState->addTime(tps);
        }
    }
}
}

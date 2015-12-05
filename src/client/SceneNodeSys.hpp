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

#ifndef VSE_RENDERSYS_HPP
#define VSE_RENDERSYS_HPP

#include <string>

#include "OgreSceneManager.h"
#include "NRES.hpp"

#include "SceneNodeComp.hpp"

namespace vse {

class SceneNodeSys : public nres::System {
public:
    SceneNodeSys(Ogre::SceneManager* smgr);
    virtual ~SceneNodeSys();
    
private:
    std::vector<nres::ComponentID> mRequiredComponents;
    std::vector<nres::Entity*> mTrackedEntities;
    
    Ogre::SceneManager* mSmgr;
    
public:
    virtual void onEntityExists(nres::Entity* entity);
    virtual void onEntityDestroyed(nres::Entity* entity);
    virtual void onEntityBroadcast(nres::Entity* entity, const EntSignal* data);
    
    virtual const std::vector<nres::ComponentID>& getRequiredComponents();
    
    std::string generateOgreEntityName();
    
    void onTick(const float& tps);
};

}

#endif // VSE_RENDERSYS_HPP

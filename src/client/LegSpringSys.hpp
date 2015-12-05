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

#ifndef vSE_LEGSPRINGSYS
#define vSE_LEGSPRINGSYS

#include "btBulletDynamicsCommon.h"

#include "NRES.hpp"

#include "RayDebugDrawer.hpp"

namespace vse {

class LegSpringSys : public nres::System {
public:
    LegSpringSys(btDiscreteDynamicsWorld* dynamicsWorld, RayDebugDrawer* rayDebugDrawer = nullptr);
    ~LegSpringSys();
    
private:
    std::vector<nres::ComponentID> mRequiredComponents;
    std::vector<nres::Entity*> mTrackedEntities;

    btDiscreteDynamicsWorld* const mDynamicsWorld;
    RayDebugDrawer* const mRayDebugDrawer;

public:
    void onEntityExists(nres::Entity* entity);
    void onEntityDestroyed(nres::Entity* entity);
    void onEntityBroadcast(nres::Entity* entity, const EntSignal* data);
    
    const std::vector<nres::ComponentID>& getRequiredComponents();
    
    void onTick();
    
};

}

#endif // vSE_LEGSPRINGSYS

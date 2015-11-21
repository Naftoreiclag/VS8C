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

#ifndef SKE_PHYSICSSYS_HPP
#define SKE_PHYSICSSYS_HPP

#include "btBulletDynamicsCommon.h"
#include "NRES.hpp"

#include "RigidBodyComp.hpp"

namespace vse {

class RigidBodySys : public nres::System {
public:
    class RigidBodyMotionListener : public btMotionState {
    protected:
        btTransform initialLoc;
        RigidBodyComp* const sendTo;
    public:
        RigidBodyMotionListener(const btTransform& initialLoc, RigidBodyComp* const sendTo);
        virtual void getWorldTransform(btTransform& worldTransform) const;
        virtual void setWorldTransform(const btTransform& worldTransform);
    };
public:
    RigidBodySys(btDynamicsWorld* dynamicsWorld);
    virtual ~RigidBodySys();
    
private:
    std::vector<nres::ComponentID> mRequiredComponents;
    std::vector<nres::Entity*> mTrackedEntities;
    
    btDynamicsWorld* mDynamicsWorld;
    
public:
    virtual void onEntityExists(nres::Entity* entity);
    virtual void onEntityDestroyed(nres::Entity* entity);
    virtual void onEntityBroadcast(nres::Entity* entity, const EntSignal* data);
    
    virtual const std::vector<nres::ComponentID>& getRequiredComponents();
    
    void onTick();
};

}

#endif // SKE_PHYSICSSYS_HPP

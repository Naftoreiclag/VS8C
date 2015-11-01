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

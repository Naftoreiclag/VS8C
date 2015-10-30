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
    RigidBodySys();
    virtual ~RigidBodySys();
    
private:
    std::vector<nres::ComponentID> requiredComponents;
    std::vector<nres::Entity*> trackedEntities;
    
    btDynamicsWorld* dynamicsWorld;
    
public:
    virtual void onEntityExists(nres::Entity* entity);
    virtual void onEntityDestroyed(nres::Entity* entity);
    virtual void onEntityBroadcast(nres::Entity* entity, const EntSignal* data);
    
    virtual const std::vector<nres::ComponentID>& getRequiredComponents();
    
    void onTick(float tps);
};

}

#endif // SKE_PHYSICSSYS_HPP

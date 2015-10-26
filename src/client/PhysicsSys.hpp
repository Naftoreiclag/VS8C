#ifndef SKE_PHYSICSSYS_HPP
#define SKE_PHYSICSSYS_HPP

#include "btBulletDynamicsCommon.h"
#include "NRES.hpp"

#include "PhysicsComp.hpp"

namespace vse {

class PhysicsSys : public nres::System {
public:
    class RigidBodyMotionListener : public btMotionState {
    protected:
        btTransform initialLoc;
        PhysicsComp* const sendTo;
    public:
        RigidBodyMotionListener(const btTransform& initialLoc, PhysicsComp* const sendTo);
        virtual void getWorldTransform(btTransform& worldTransform) const;
        virtual void setWorldTransform(const btTransform& worldTransform);
    };
public:
    PhysicsSys();
    virtual ~PhysicsSys();
    
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

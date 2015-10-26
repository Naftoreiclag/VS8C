#ifndef VSE_RENDERSYS_HPP
#define VSE_RENDERSYS_HPP

#include <string>

#include "btBulletDynamicsCommon.h"
#include "OgreSceneManager.h"
#include "NRES.hpp"

#include "PhysicsComp.hpp"

namespace vse {

class RenderSys : public nres::System {
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
    RenderSys();
    virtual ~RenderSys();
    
private:
    std::vector<nres::ComponentID> requiredComponents;
    std::vector<nres::Entity*> trackedEntities;
    
    Ogre::SceneManager* smgr;
    btDynamicsWorld* dynamicsWorld;
    
public:
    virtual void onEntityExists(nres::Entity* entity);
    virtual void onEntityDestroyed(nres::Entity* entity);
    virtual void onEntityBroadcast(nres::Entity* entity, const EntSignal* data);
    
    virtual const std::vector<nres::ComponentID>& getRequiredComponents();
    
    void onTick(float tps);
    std::string generateOgreEntityName();
};

}

#endif // VSE_RENDERSYS_HPP

#ifndef VSE_RENDERSYS_HPP
#define VSE_RENDERSYS_HPP

#include <string>

#include "OgreSceneManager.h"
#include "NRES.hpp"

#include "SceneNodeComp.hpp"

namespace vse {

class RenderSys : public nres::System {
public:
    RenderSys();
    virtual ~RenderSys();
    
private:
    std::vector<nres::ComponentID> requiredComponents;
    std::vector<nres::Entity*> trackedEntities;
    
    Ogre::SceneManager* smgr;
    
public:
    virtual void onEntityExists(nres::Entity* entity);
    virtual void onEntityDestroyed(nres::Entity* entity);
    virtual void onEntityBroadcast(nres::Entity* entity, const EntSignal* data);
    
    virtual const std::vector<nres::ComponentID>& getRequiredComponents();
    
    std::string generateOgreEntityName();
};

}

#endif // VSE_RENDERSYS_HPP

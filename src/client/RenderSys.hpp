#ifndef VSE_RENDERSYS_HPP
#define VSE_RENDERSYS_HPP

#include <string>

#include "OgreSceneManager.h"
#include "NRES.hpp"

#include "SceneNodeComp.hpp"

namespace vse {

class RenderSys : public nres::System {
public:
    RenderSys(Ogre::SceneManager* smgr);
    virtual ~RenderSys();
    
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
};

}

#endif // VSE_RENDERSYS_HPP

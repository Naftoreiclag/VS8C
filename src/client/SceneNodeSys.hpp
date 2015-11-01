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
};

}

#endif // VSE_RENDERSYS_HPP

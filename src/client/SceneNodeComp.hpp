#ifndef VSE_SCENENODECOMP_HPP
#define VSE_SCENENODECOMP_HPP

#include <string>

#include "OgreSceneNode.h"
#include "OgreEntity.h"

#include "NRES.hpp"

namespace vse {

class SceneNodeComp : public nres::Component
{
public:
    SceneNodeComp(std::string resname);
    virtual ~SceneNodeComp();
    
    static const nres::ComponentID componentID;
    virtual const nres::ComponentID& getID() const;
    
    Ogre::SceneNode* mSceneNode;
    Ogre::Entity* mOgreEntity;
    
    std::string mResourceName;

};

}

#endif // VSE_SCENENODECOMP_HPP

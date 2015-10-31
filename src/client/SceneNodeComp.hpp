#ifndef VSE_SCENENODECOMP_HPP
#define VSE_SCENENODECOMP_HPP

#include "OgreSceneNode.h"
#include "OgreEntity.h"

#include "NRES.hpp"

namespace vse {

class SceneNodeComp : public nres::Component
{
public:
    SceneNodeComp();
    virtual ~SceneNodeComp();
    
    static const nres::ComponentID componentID;
    virtual const nres::ComponentID& getID() const;
    
    Ogre::SceneNode* boxNode;
    Ogre::Entity* boxModel;

};

}

#endif // VSE_SCENENODECOMP_HPP

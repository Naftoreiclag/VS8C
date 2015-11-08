#ifndef VSE_SCENENODECOMP_HPP
#define VSE_SCENENODECOMP_HPP

#include <string>

#include "OgreSceneNode.h"
#include "OgreEntity.h"

#include "NRES.hpp"

#include "Vec3f.hpp"

namespace vse {

class SceneNodeComp : public nres::Component
{
public:
    SceneNodeComp(const std::string& resname, const Vec3f& nodeOffset = Vec3f(0, 0, 0));
    virtual ~SceneNodeComp();
    
    static const nres::ComponentID componentID;
    virtual const nres::ComponentID& getID() const;
    
    Ogre::SceneNode* mSceneNode;
    Ogre::Entity* mOgreEntity;
    
    std::string mResourceName;
    
    Vec3f mSceneNodeOffset;

};

}

#endif // VSE_SCENENODECOMP_HPP

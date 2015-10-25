#ifndef SKE_BOXCOMP_HPP
#define SKE_BOXCOMP_HPP

#include "OgreSceneNode.h"
#include "OgreEntity.h"

#include "NRES.hpp"

namespace vse {

class BoxComp : public nres::Component
{
public:
    static const nres::ComponentID componentID;
    BoxComp();
    virtual ~BoxComp();
    
    Ogre::SceneNode* boxNode;
    Ogre::Entity* boxModel;
    
    float x;
public:
    virtual const nres::ComponentID& getID();

};

}

#endif // SKE_BOXCOMP_HPP

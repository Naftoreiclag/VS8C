/*
   Copyright 2015 James Fong

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

*/

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

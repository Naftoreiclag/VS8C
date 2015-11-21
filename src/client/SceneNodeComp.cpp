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

#include "SceneNodeComp.hpp"

namespace vse {
    
const nres::ComponentID SceneNodeComp::componentID = "sceneN";

SceneNodeComp::SceneNodeComp(const std::string& resname, const Vec3f& nodeOffset)
: mResourceName(resname)
, mSceneNodeOffset(nodeOffset) {
}

SceneNodeComp::~SceneNodeComp() {
}

const nres::ComponentID& SceneNodeComp::getID() const {
    return componentID;
}

}

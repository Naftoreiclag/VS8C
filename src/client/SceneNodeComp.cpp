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

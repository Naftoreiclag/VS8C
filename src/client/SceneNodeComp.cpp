#include "SceneNodeComp.hpp"

namespace vse {
    
const nres::ComponentID SceneNodeComp::componentID = "sceneN";

SceneNodeComp::SceneNodeComp(std::string resname)
: mResourceName(resname) {
}

SceneNodeComp::~SceneNodeComp() {
}

const nres::ComponentID& SceneNodeComp::getID() const {
    return componentID;
}

}

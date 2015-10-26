#include "SceneNodeComp.hpp"

namespace vse
{
const nres::ComponentID SceneNodeComp::componentID = "sceneN";

SceneNodeComp::SceneNodeComp() {
}

SceneNodeComp::~SceneNodeComp() {
}

const nres::ComponentID& SceneNodeComp::getID() {
    return componentID;
}

}

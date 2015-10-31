#include "LocalPlayerComp.hpp"

namespace vse {
    
const nres::ComponentID LocalPlayerComp::componentID = "localpl";

LocalPlayerComp::LocalPlayerComp() {
}

LocalPlayerComp::~LocalPlayerComp() {
}

const nres::ComponentID& LocalPlayerComp::getID() const {
    return componentID;
}

}


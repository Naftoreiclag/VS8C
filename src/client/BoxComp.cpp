#include "BoxComp.hpp"

namespace vse {
    
const nres::ComponentID BoxComp::componentID = "box";

BoxComp::BoxComp()
{
    x = 0;
}

BoxComp::~BoxComp()
{
}

const nres::ComponentID& BoxComp::getID() {
    return componentID;
}


}


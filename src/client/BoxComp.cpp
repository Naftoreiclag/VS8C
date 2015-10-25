#include "BoxComp.hpp"

namespace vse
{
    
const nres::ComponentID BoxComp::staticID = "box";

BoxComp::BoxComp()
{
}

BoxComp::~BoxComp()
{
}

const nres::ComponentID& BoxComp::getID() {
    return staticID;
}


}


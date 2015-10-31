#include "LegSpringComp.hpp"

namespace vse
{

const nres::ComponentID LegSpringComp::componentID = "sprleg";

LegSpringComp::LegSpringComp()
{
}

LegSpringComp::~LegSpringComp()
{
}

const nres::ComponentID& LegSpringComp::getID() const {
    return componentID;
}


}


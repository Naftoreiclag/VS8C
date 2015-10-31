#ifndef NRES_COMPONENT_HPP
#define NRES_COMPONENT_HPP

#include "nresTypedefs.hpp"

namespace nres
{

class Component
{
public:
    Component();
    virtual ~Component();
public:
    virtual const ComponentID& getID() const = 0;
};

}

#endif // NRES_COMPONENT_HPP

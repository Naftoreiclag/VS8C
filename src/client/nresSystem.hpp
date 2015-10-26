#ifndef NRES_SYSTEM_HPP
#define NRES_SYSTEM_HPP

#include <vector>

#include "nresTypedefs.hpp"
#include "nresEntity.hpp"

#include "EntSignal.hpp"

namespace nres
{

class System {
public:
    System();
    virtual ~System();
public:
    virtual void onEntityExists(Entity* entity) = 0;
    virtual void onEntityDestroyed(Entity* entity) = 0;
    virtual void onEntityBroadcast(Entity* entity, const vse::EntSignal* data) = 0;
    
    virtual const std::vector<ComponentID>& getRequiredComponents() = 0;
};

}

#endif // NRES_SYSTEM_HPP

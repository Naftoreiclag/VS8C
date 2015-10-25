#ifndef NRES_SYSTEM_HPP
#define NRES_SYSTEM_HPP

#include "nresTypedefs.hpp"
#include "nresEntity.hpp"

#include <vector>

namespace nres
{

class System {
public:
    System();
    virtual ~System();
public:
    virtual void entityExists(Entity* entity) = 0;
    virtual void entityDestroyed(Entity* entity) = 0;
    virtual void entityBroadcasted(Entity* entity, void* data) = 0;
    
    virtual const std::vector<ComponentID>& getRequiredComponents() = 0;
};

}

#endif // NRES_SYSTEM_HPP

#ifndef NRES_LISTENER_HPP
#define NRES_LISTENER_HPP

#include "EntSignal.hpp"

namespace nres {
    
class Entity;
class Listener {
public:
    Listener();
    virtual ~Listener();
public:
    virtual void onEntityExists(Entity* entity) = 0;
    virtual void onEntityDestroyed(Entity* entity) = 0;
    virtual void onEntityBroadcast(Entity* entity, const vse::EntSignal* data) = 0;
};

}

#endif // NRES_LISTENER_HPP

#ifndef vSE_LEGSPRINGSYS
#define vSE_LEGSPRINGSYS

#include "btBulletDynamicsCommon.h"

#include "NRES.hpp"

namespace vse {

class LegSpringSys : public nres::System {
public:
    LegSpringSys(btDiscreteDynamicsWorld* const dynamicsWorld);
    virtual ~LegSpringSys();
    
private:
    std::vector<nres::ComponentID> mRequiredComponents;
    std::vector<nres::Entity*> mTrackedEntities;

    btDiscreteDynamicsWorld* const mDynamicsWorld;

public:
    virtual void onEntityExists(nres::Entity* entity);
    virtual void onEntityDestroyed(nres::Entity* entity);
    virtual void onEntityBroadcast(nres::Entity* entity, const EntSignal* data);
    
    virtual const std::vector<nres::ComponentID>& getRequiredComponents();
    
    void onTick();
    
};

}

#endif // vSE_LEGSPRINGSYS

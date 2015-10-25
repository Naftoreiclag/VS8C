#ifndef SKE_BOXSYS_HPP
#define SKE_BOXSYS_HPP

#include "NRES.hpp"

namespace vse
{

class BoxSys : public nres::System
{
public:
    BoxSys();
    virtual ~BoxSys();
    
private:
    std::vector<nres::ComponentID> requiredComponents;
    std::vector<nres::Entity*> trackedEntities;
    
public:
    virtual void entityExists(nres::Entity* entity);
    virtual void entityDestroyed(nres::Entity* entity);
    virtual void entityBroadcasted(nres::Entity* entity, void* data);
    
    virtual const std::vector<nres::ComponentID>& getRequiredComponents();
    
    void tick(float tps);
};

}

#endif // SKE_BOXSYS_HPP

#ifndef VSE_SCENENODECOMP_HPP
#define VSE_SCENENODECOMP_HPP

#include "NRES.hpp"

namespace vse {

class SceneNodeComp : public nres::Component
{
public:
    SceneNodeComp();
    virtual ~SceneNodeComp();
    
    static const nres::ComponentID componentID;
    virtual const nres::ComponentID& getID();

};

}

#endif // VSE_SCENENODECOMP_HPP

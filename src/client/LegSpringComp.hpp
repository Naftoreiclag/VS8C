#ifndef VSE_LEGSPRING_COMP
#define VSE_LEGSPRING_COMP

#include "NRES.hpp"

namespace vse {

class LegSpringComp : public nres::Component {
public:
    LegSpringComp();
    virtual <~LegSpringComp();
    
    static const nres::ComponentID componentID;
    virtual const nres::ComponentID& getID();

};

}

#endif // VSE_LEGSPRING_COMP

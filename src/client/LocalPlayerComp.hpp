#ifndef VSE_LOCALPLAYERCOMP_HPP
#define VSE_LOCALPLAYERCOMP_HPP

#include "NRES.hpp"

namespace vse {

class LocalPlayerComp : public nres::Component
{
public:
    LocalPlayerComp();
    virtual ~LocalPlayerComp();
    
    static const nres::ComponentID componentID;
    virtual const nres::ComponentID& getID();

};

}

#endif // VSE_LOCALPLAYERCOMP_HPP

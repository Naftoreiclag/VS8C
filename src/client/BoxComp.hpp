#ifndef SKE_BOXCOMP_HPP
#define SKE_BOXCOMP_HPP

#include "NRES.hpp"

namespace vse
{

class BoxComp : public nres::Component
{
public:
    BoxComp();
    ~BoxComp();
    
    float x;
    
public:
    virtual const nres::ComponentID& getID();
    static const nres::ComponentID staticID;

};

}

#endif // SKE_BOXCOMP_HPP

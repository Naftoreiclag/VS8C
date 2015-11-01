#ifndef VSE_LOCALPLAYERMOVESIGNAL_HPP
#define VSE_LOCALPLAYERMOVESIGNAL_HPP

#include "EntSignal.hpp"
#include "Vec3f.hpp"

namespace vse {

class WalkSignal : public EntSignal {
public:
    WalkSignal(Vec3f requestedMovement);
    virtual ~WalkSignal();

    virtual EntSignal::Type getType() const;
    
    Vec3f requestedMovement;
};

}

#endif // VSE_LOCALPLAYERMOVESIGNAL_HPP

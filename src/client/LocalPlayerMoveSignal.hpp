#ifndef VSE_LOCALPLAYERMOVESIGNAL_HPP
#define VSE_LOCALPLAYERMOVESIGNAL_HPP

#include "EntSignal.hpp"
#include "Vec3f.hpp"

namespace vse {

class LocalPlayerMoveSignal : public EntSignal {
public:
    LocalPlayerMoveSignal(Vec3f requestedMovement);
    virtual ~LocalPlayerMoveSignal();

    virtual EntSignal::Type getType() const;
    
    Vec3f requestedMovement;
};

}

#endif // VSE_LOCALPLAYERMOVESIGNAL_HPP

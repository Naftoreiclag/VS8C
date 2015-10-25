#ifndef VSE_LOCALPLAYERMOVESIGNAL_HPP
#define VSE_LOCALPLAYERMOVESIGNAL_HPP

#include "EntSignal.hpp"

namespace vse {

class LocalPlayerMoveSignal : public EntSignal {
public:
    LocalPlayerMoveSignal();
    virtual ~LocalPlayerMoveSignal();

    virtual EntSignal::Type getType();
};

}

#endif // VSE_LOCALPLAYERMOVESIGNAL_HPP

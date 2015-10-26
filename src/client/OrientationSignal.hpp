#ifndef VSE_ORIENATIONSIGNAL_HPP
#define VSE_ORIENATIONSIGNAL_HPP

#include "EntSignal.hpp"
#include "Quate.hpp"

namespace vse {

class OrientationSignal : public EntSignal {
public:
    OrientationSignal(Quate orienationUpdate);
    virtual ~OrientationSignal();

    virtual EntSignal::Type getType() const;
    
    Quate mOrienationUpdate;
};

}

#endif // VSE_ORIENATIONSIGNAL_HPP

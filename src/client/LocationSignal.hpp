#ifndef VSE_LOCATIONSIGNAL_HPP
#define VSE_LOCATIONSIGNAL_HPP

#include "EntSignal.hpp"
#include "Vec3f.hpp"

namespace vse {

class LocationSignal : public EntSignal {
public:
    LocationSignal(Vec3f locationUpdate);
    virtual ~LocationSignal();

    virtual EntSignal::Type getType() const;
    
    Vec3f mLocationUpdate;
};

}

#endif // VSE_LOCATIONSIGNAL_HPP

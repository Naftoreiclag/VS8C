#include "LocationSignal.hpp"

namespace vse {

LocationSignal::LocationSignal(Vec3f locationUpdate)
: mLocationUpdate(locationUpdate) {
}

LocationSignal::~LocationSignal() {
}

EntSignal::Type LocationSignal::getType() const {
    return EntSignal::Type::LOCATION;
}

}

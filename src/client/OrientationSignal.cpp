#include "OrientationSignal.hpp"

namespace vse {

OrientationSignal::OrientationSignal(Quate orienationUpdate)
: mOrientationUpdate(orienationUpdate) {
}

OrientationSignal::~OrientationSignal() {
}

EntSignal::Type OrientationSignal::getType() const {
    return EntSignal::Type::ORIENTATION;
}

}

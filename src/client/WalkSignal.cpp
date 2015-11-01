#include "WalkSignal.hpp"

namespace vse
{

WalkSignal::WalkSignal(Vec3f requestedMovement)
: requestedMovement(requestedMovement) {
}

WalkSignal::~WalkSignal()
{
}

EntSignal::Type WalkSignal::getType() const {
    return EntSignal::Type::REQ_WALK;
}

}


#include "LocalPlayerMoveSignal.hpp"

namespace vse
{

LocalPlayerMoveSignal::LocalPlayerMoveSignal(Vec3f requestedMovement)
: requestedMovement(requestedMovement) {
}

LocalPlayerMoveSignal::~LocalPlayerMoveSignal()
{
}

EntSignal::Type LocalPlayerMoveSignal::getType() const {
    return EntSignal::Type::LOCAL_PLAYER_MOVE;
}

}


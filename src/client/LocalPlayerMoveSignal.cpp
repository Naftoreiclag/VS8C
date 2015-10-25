#include "LocalPlayerMoveSignal.hpp"

namespace vse
{

LocalPlayerMoveSignal::LocalPlayerMoveSignal()
{
}

LocalPlayerMoveSignal::~LocalPlayerMoveSignal()
{
}

EntSignal::Type LocalPlayerMoveSignal::getType() {
    return EntSignal::Type::LOCAL_PLAYER_MOVE;
}

}


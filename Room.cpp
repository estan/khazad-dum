#include "Room.h"

namespace kd {

Room::Room(Game* game, std::istream& in) : Environment(game, in)
{
}

bool Room::enter()
{
    return true;
}

bool Room::leave()
{
    return true;
}

} // namespace kd

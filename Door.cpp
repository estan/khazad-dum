#include "Door.h"

namespace kd {

Door::Door(Game* game, std::istream& in) : Exit(game, in)
{
    in >> destinationId_;
}

Door::~Door()
{
}

bool Door::open()
{
    return true;
}

bool Door::visible() const
{
    return true;
}

std::string Door::destinationId() const
{
    return destinationId_;
}

} // namespace kd

#include "HiddenDoor.h"

#include "Game.h"
#include "Print.h"

namespace kd {

HiddenDoor::HiddenDoor(Game* game, std::istream& in) : Door(game, in)
{
}

bool HiddenDoor::open()
{
    printl("You go through a hidden door!");
    return true;
}

bool HiddenDoor::visible() const
{
    return false;
}

} // namespace kd

#include "NocturnalDoor.h"

#include "Game.h"
#include "Print.h"

namespace kd {

NocturnalDoor::NocturnalDoor(Game* game, std::istream& in) : Door(game, in)
{
}

bool NocturnalDoor::open()
{
    if (game()->time() == Game::Night) {
        return true;
    } else {
        printl("The %1 is nocturnal and only available during the night.", description());
        return false;
    }
}

bool NocturnalDoor::visible() const
{
    return true;
}

} // namespace kd

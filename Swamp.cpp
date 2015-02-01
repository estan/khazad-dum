#include "Swamp.h"

#include "Environment.h"
#include "Game.h"
#include "Player.h"
#include "Print.h"

#include <memory>

namespace kd {

Swamp::Swamp(Game* game, std::istream &in) : Environment(game, in)
{
    in >> damage_;
}

bool Swamp::enter()
{
    return true;
}

bool Swamp::leave() {
    game()->player()->inflict(damage_);

    printl("You lost %1 HP in getting through the swamp.", damage_);
    printl("Your current HP is %1.", game()->player()->hp());

    return true;
}

} // namespace kd

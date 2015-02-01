#include "Bridge.h"

#include "Game.h"
#include "Player.h"
#include "Print.h"
#include "Random.h"

#include <memory>

namespace kd {

Bridge::Bridge(Game* game, std::istream& in) : Exit(game, in)
{
    in >> destinationId_;
    in >> stability_;
}

bool Bridge::open()
{
    printl("The bridge makes some cracking sounds as you walk on it.");

    if (stability_ < random::probability()) {
        printl("The bridge collapses under you!");
        game()->player()->kill();
        return false;
    }

    printl("You make it safely across the bridge.");

    return true;
}

bool Bridge::visible() const
{
    return true;
}

std::string Bridge::destinationId() const
{
    return destinationId_;
}

} // namespace kd

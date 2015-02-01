#include "Portal.h"

#include "Exit.h"
#include "Print.h"
#include "Random.h"

namespace kd {

Portal::Portal(Game* game, std::istream& in) : Exit(game, in)
{
    int numDestinationIds;
    in >> numDestinationIds;

    for (int i = 0; i < numDestinationIds; ++i) {
        std::string destinationId;
        in >> destinationId;
        destinationIds_.push_back(destinationId);
    }

    index_ = std::uniform_int_distribution<int>(0, destinationIds_.size() - 1);
}

bool Portal::open()
{
    printl("Your head starts spinning as you pass through a portal!");
    printl("You're being transported to a random location.");

    return true;
}

bool Portal::visible() const
{
    return true;
}

std::string Portal::destinationId() const
{
    return destinationIds_.at(index_(random::engine()));
}

} // namespace kd

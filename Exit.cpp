#include "Exit.h"

#include "Bridge.h"
#include "Door.h"
#include "Game.h"
#include "HiddenDoor.h"
#include "LockedDoor.h"
#include "NocturnalDoor.h"
#include "Portal.h"

#include <iomanip>
#include <stdexcept>

namespace kd {

Exit::Exit(Game* game, std::istream& in) : game_(game)
{
    in >> std::quoted(description_);
    in >> std::quoted(detailedDescription_);
    in >> direction_;
    in >> sourceId_;
}

Exit::~Exit()
{
}

std::string Exit::description() const
{
    return description_;
}

std::string Exit::detailedDescription() const
{
    return detailedDescription_;
}

std::string Exit::direction() const
{
    return direction_;
}

std::shared_ptr<Environment> Exit::source() const
{
    return game_->environment(sourceId_);
}

std::shared_ptr<Environment> Exit::destination() const
{
    return game_->environment(destinationId());
}

std::shared_ptr<Exit> Exit::load(Game* game, std::istream &in)
{
    std::string type;
    in >> type;

    if (type == "Door") {
        return std::make_shared<Door>(game, in);
    } else if (type == "NocturnalDoor") {
        return std::make_shared<NocturnalDoor>(game, in);
    } else if (type == "HiddenDoor") {
        return std::make_shared<HiddenDoor>(game, in);
    } else if (type == "LockedDoor") {
        return std::make_shared<LockedDoor>(game, in);
    } else if (type == "Portal") {
        return std::make_shared<Portal>(game, in);
    } else if (type == "Bridge") {
        return std::make_shared<Bridge>(game, in);
    } else {
        throw std::runtime_error("Unknown exit type " + type);
    }
}

Game* Exit::game() const
{
    return game_;
}

std::ostream& operator<<(std::ostream& out, const Exit& exit) {
    return out << exit.description();
}

} // namespace kd

#include "Actor.h"

#include "Dwarf.h"
#include "Elf.h"
#include "Wizard.h"

#include <iomanip>
#include <stdexcept>

namespace kd {

Actor::Actor(Game* game, std::istream& in) : game_(game)
{
    in >> id_;
    in >> std::quoted(description_);
    in >> std::quoted(detailedDescription_);
}

Actor::~Actor()
{
}

std::string Actor::id() const
{
    return id_;
}

std::string Actor::description() const
{
    return description_;
}

std::string Actor::detailedDescription() const
{
    return detailedDescription_;
}

std::shared_ptr<Actor> Actor::load(Game* game, std::istream& in)
{
    std::string type;
    in >> type;

    if (type == "Wizard") {
        return std::make_shared<Wizard>(game, in);
    } else if (type == "Dwarf") {
        return std::make_shared<Dwarf>(game, in);
    } else if (type == "Elf") {
        return std::make_shared<Elf>(game, in);
    } else {
        throw std::runtime_error("Unknown actor type " + type);
    }
}

Game* Actor::game() const
{
    return game_;
}

} // namespace kd

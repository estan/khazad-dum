#include "Item.h"

#include <iomanip>
#include <stdexcept>

namespace kd {

Item::Item(std::istream& in)
{
    std::string type;
    in >> type;

    if (type != "Item") {
        throw std::runtime_error("invalid item type " + type);
    }

    in >> id_;
    in >> std::quoted(description_);
    in >> std::quoted(detailedDescription_);
    in >> damage_;
    in >> protection_;
    in >> nutrition_;
}

std::string Item::id() const
{
    return id_;
}

std::string Item::description() const
{
    return description_;
}

std::string Item::detailedDescription() const
{
    return detailedDescription_;
}

int Item::damage() const
{
    return damage_;
}

int Item::protection() const
{
    return protection_;
}

int Item::nutrition() const
{
    return nutrition_;
}

} // namespace kd

#ifndef DWARF_H
#define DWARF_H

#include "Actor.h"

#include <istream>
#include <memory>
#include <vector>

namespace kd {

class Game;
class Item;

class Dwarf : public Actor
{
public:
    Dwarf(Game* game, std::istream& in);

    virtual void act() override;
    virtual void talk() override;

private:
    std::vector<std::shared_ptr<Item>> items_;
};

} // namespace kd

#endif // DWARF_H

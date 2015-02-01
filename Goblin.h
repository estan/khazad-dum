#ifndef GOBLIN_H
#define GOBLIN_H

#include "Enemy.h"

#include <istream>
#include <memory>
#include <set>

namespace kd {

class Game;
class Item;

class Goblin : public Enemy
{
public:
    Goblin(Game* game, std::istream& in);

    virtual void act() override;

private:
    std::set<std::shared_ptr<Item>> stolenItems_;
};

} // namespace kd

#endif // GOBLIN_H

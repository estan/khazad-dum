#ifndef WIZARD_H
#define WIZARD_H

#include "Actor.h"

#include <istream>
#include <memory>
#include <string>

namespace kd {

class Game;
class Item;

class Wizard : public Actor
{
public:
    Wizard(Game* game, std::istream& in);

    virtual void act() override;
    virtual void talk() override;

private:
    std::string riddle_;
    std::string answer_;
    std::shared_ptr<Item> reward_;
};

} // namespace kd

#endif // WIZARD_H

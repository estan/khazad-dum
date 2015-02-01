#ifndef ORC_H
#define ORC_H

#include "Enemy.h"

#include <istream>

namespace kd {

class Game;

class Orc : public Enemy
{
public:
    Orc(Game* game, std::istream& in);

    virtual void act() override;
};

} // namespace kd

#endif // ORC_H

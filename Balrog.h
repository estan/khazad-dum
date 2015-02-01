#ifndef BALROG_H
#define BALROG_H

#include "Enemy.h"

#include <istream>

namespace kd {

class Game;

class Balrog : public Enemy
{
public:
    Balrog(Game* game, std::istream& in);
};

} // namespace kd

#endif // BALROG_H

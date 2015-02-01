#ifndef SWAMP_H
#define SWAMP_H

#include "Environment.h"

#include <istream>

namespace kd {

class Game;

class Swamp : public Environment
{
public:
    Swamp(Game * game, std::istream& in);

    virtual bool enter() override;
    virtual bool leave() override;

private:
    int damage_;
};

} // namespace kd

#endif // SWAMP_H

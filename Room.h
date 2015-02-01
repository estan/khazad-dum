#ifndef ROOM_H
#define ROOM_H

#include "Environment.h"

#include <istream>

namespace kd {

class Game;

class Room : public Environment
{
public:
    Room(Game* game, std::istream& in);

    virtual bool enter() override;
    virtual bool leave() override;
};

} // namespace kd

#endif // ROOM_H

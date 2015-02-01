#ifndef NOCTURNAL_DOOR_H
#define NOCTURNAL_DOOR_H

#include "Door.h"

#include <istream>

namespace kd {

class Game;

class NocturnalDoor : public Door
{
public:
    NocturnalDoor(Game* game, std::istream& in);

    virtual bool open() override;
    virtual bool visible() const override;
};

} // namespace kd

#endif // NOCTURNAL_DOOR_H

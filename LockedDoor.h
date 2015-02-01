#ifndef LOCKED_DOOR_H
#define LOCKED_DOOR_H

#include "Door.h"

#include <istream>
#include <string>

namespace kd {

class Game;

class LockedDoor : public Door
{
public:
    LockedDoor(Game* game, std::istream& in);

    virtual bool open() override;
    virtual bool visible() const override;

private:
    std::string keyItemId_;
};

} // namespace kd

#endif // LOCKED_DOOR_H

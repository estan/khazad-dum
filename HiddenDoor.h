#ifndef HIDDEN_DOOR_H
#define HIDDEN_DOOR_H

#include "Door.h"

#include <istream>

namespace kd {

class Game;

class HiddenDoor : public Door
{
public:
    HiddenDoor(Game* game, std::istream& in);

    virtual bool open() override;
    virtual bool visible() const override;
};

} // namespace kd

#endif // HIDDEN_DOOR_H

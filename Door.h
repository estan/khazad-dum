#ifndef DOOR_H
#define DOOR_H

#include "Exit.h"

#include <istream>
#include <string>

namespace kd {

class Game;

class Door : public Exit
{
public:
    Door(Game* game, std::istream& in);
    virtual ~Door();

    virtual bool open() override;
    virtual bool visible() const override;

protected:
    virtual std::string destinationId() const override;

private:
    std::string destinationId_;
};

} // namespace kd

#endif // DOOR_H

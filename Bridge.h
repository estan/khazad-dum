#ifndef BRIDGE_H
#define BRIDGE_H

#include "Exit.h"

#include <istream>
#include <string>

namespace kd {

class Game;

class Bridge : public Exit
{
public:
    Bridge(Game* game, std::istream& in);

    virtual bool open() override;
    virtual bool visible() const override;

    double instability() const;

protected:
    virtual std::string destinationId() const override;

private:
    std::string destinationId_;
    double stability_;
};

} // namespace kd

#endif // BRIDGE_H

#ifndef PORTAL_H
#define PORTAL_H

#include "Exit.h"

#include <istream>
#include <vector>
#include <random>
#include <string>

namespace kd {

class Game;

class Portal : public Exit
{
public:
    Portal(Game* game, std::istream& in);

    virtual bool open() override;
    virtual bool visible() const override;

protected:
    virtual std::string destinationId() const override;

private:
    std::vector<std::string> destinationIds_;
    mutable std::uniform_int_distribution<int> index_;
};

} // namespace kd

#endif // PORTAL_H

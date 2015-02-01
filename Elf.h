#ifndef ELF_H
#define ELF_H

#include "Actor.h"

#include <istream>
#include <string>

namespace kd {

class Game;

class Elf : public Actor
{
public:
    Elf(Game* game, std::istream& in);

    virtual void act() override;
    virtual void talk() override;

private:
    std::string clue_;
};

} // namespace kd

#endif // ELF_H

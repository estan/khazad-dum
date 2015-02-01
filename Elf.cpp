#include "Elf.h"

#include "Print.h"

#include <iomanip>

namespace kd {

Elf::Elf(Game* game, std::istream& in) : Actor(game, in)
{
    in >> std::quoted(clue_);
}

void Elf::act()
{
    printl("A %1 is standing tall.", description());
}

void Elf::talk() {
    printl("%1: Let me give you a clue: %2.", id(), clue_);
}

} // namespace kd

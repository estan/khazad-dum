#include "LockedDoor.h"

#include "Game.h"
#include "Item.h"
#include "Player.h"
#include "Print.h"

namespace kd {

LockedDoor::LockedDoor(Game* game, std::istream& in) : Door(game, in)
{
    in >> keyItemId_;
}

bool LockedDoor::open()
{
    if (const auto& item = game()->player()->item(keyItemId_)) {
        printl("You use the %1 to open the %2.", item->description(), description());
        return true;
    } else {
        printl("The door is locked. You need %1 to open it.", keyItemId_);
        return false;
    }
}

bool LockedDoor::visible() const
{
    return true;
}

} // namespace kd

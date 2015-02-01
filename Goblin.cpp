#include "Goblin.h"

#include "Environment.h"
#include "Game.h"
#include "Item.h"
#include "Player.h"
#include "Print.h"
#include "Random.h"

#include <algorithm>

namespace kd {

Goblin::Goblin(Game* game, std::istream& in) : Enemy(game, in)
{
}

void Goblin::act()
{
    Enemy::act();

    if (random::probability() > 0.9) {
        // Steal a random item.
        if (!game()->player()->items().empty()) {
            auto items = game()->player()->items();
            std::random_shuffle(items.begin(), items.end());
            auto stolenItem = game()->player()->removeItem(items.front()->id());
            stolenItems_.insert(stolenItem);
            printl("%1 stole your %2!", id(), stolenItem->description());
        }
    }

    if (hp() <= game()->player()->damage()) {
        // Almost dead, so drop all stolen items.
        for (const auto& item : stolenItems_) {
            game()->player()->environment()->addItem(item);
            printl("%1 dropped a %2 on the ground.", id(), item->description());
        }
        stolenItems_.clear();
    }
}

} // namespace kd

#include "Orc.h"

#include "Game.h"
#include "Item.h"
#include "Player.h"
#include "Print.h"
#include "Random.h"

#include <algorithm>
#include <memory>
#include <vector>

namespace kd {

Orc::Orc(Game* game, std::istream& in) : Enemy(game, in)
{
}

void Orc::act()
{
    Enemy::act();

    if (random::probability() > 0.9) {
        // Steal and eat a random edible item.
        std::vector<std::shared_ptr<Item>> edibleItems;
        for (const auto& item : game()->player()->items()) {
            if (item->nutrition() > 0) {
                edibleItems.push_back(item);
            }
        }
        if (!edibleItems.empty()) {
            std::random_shuffle(edibleItems.begin(), edibleItems.end());
            auto item = game()->player()->removeItem(edibleItems.front()->id());
            printl("%1 stole your %2 and ate it!", id(), item->description());
        }
    }
}

} // namespace kd

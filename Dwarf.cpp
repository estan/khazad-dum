#include "Dwarf.h"

#include "Game.h"
#include "Input.h"
#include "Item.h"
#include "Player.h"
#include "Print.h"

#include <algorithm>

namespace kd {

Dwarf::Dwarf(Game* game, std::istream& in) : Actor(game, in)
{
    int numItems;
    in >> numItems;
    for (int i = 0; i < numItems; ++i) {
        items_.push_back(std::make_shared<Item>(in));
    }
}

void Dwarf::act()
{
    if (game()->time() == Game::Night) {
        printl("A %1 is walking around, looking anxious to trade.", description());
    } else {
        printl("A %1 is sleeping on the ground. He is snooring.", description());
    }
}

void Dwarf::talk() {
    if (game()->time() != Game::Night) {
        printl("The %1 is sleeping like a stone.", description());
        return;
    }

    if (game()->player()->items().empty()) {
        printl("%1: I don't want to talk. You don't seem to have anything "
               "to trade. Come back another time.", id());
        return;
    }

    printl("%1: What do you have to give me? I'll trade you anything"
           " as long as I can decide what! I currently have:", id());

    for (const auto& item : items_) {
        printl("  %1: %2", item->id(), item->description());
    }

    while (true) {
        std::string itemId = input::line("Item to trade away ('no' to cancel): ");

        if (itemId == "no") {
            break;
        }

        if (const auto& item = game()->player()->removeItem(itemId)) {
            std::random_shuffle(items_.begin(), items_.end());
            const auto reward = items_.back();

            printl("%1: Oh wow, a %2. For that I'll give you a %3",
                   id(), item->description(), reward->description());

            items_.pop_back();
            game()->player()->addItem(reward);
            items_.push_back(item);

            printl("You got a %1!", reward->description());

            break;
        } else {
            printl("You don't have any such item. You currently have:");
            for (const auto& item : game()->player()->items()) {
                printl("  %1: %2", item->id(), item->description());
            }
        }
    }
}

} // namespace kd

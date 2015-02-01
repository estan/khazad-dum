#include "Wizard.h"

#include "Game.h"
#include "Input.h"
#include "Item.h"
#include "Player.h"
#include "Print.h"

#include <algorithm>
#include <iomanip>

namespace kd {

Wizard::Wizard(Game* game, std::istream& in) : Actor(game, in)
{
    in >> std::quoted(riddle_);
    in >> std::quoted(answer_);
    reward_ = std::make_shared<Item>(in);
}

void Wizard::act()
{
    if (game()->time() == Game::Night) {
        printl("A %1 is asleep, floating in the air.", description());
    } else if (game()->time() == Game::Morning) {
        printl("A %1 is sitting on the ground.", description());
    } else {
        printl("A %1 is pacing back and forth.", description());
    }
}

void Wizard::talk() {
    if (game()->time() == Game::Night) {
        printl("Do not disturb a sleeping wizard, he might put a spell on you!");
    } else if (reward_) {
        printl("%1: I will award you a %2, if you can answer this riddle: %3",
               id(), reward_->description(), riddle_);

        std::string answer = input::line("Answer: ");
        std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

        if (answer == answer_) {
            printl("%1: Correct! I will give you a %2!", id(), reward_->description());
            game()->player()->addItem(reward_);
            printl("You got a %1!", reward_->description());
            reward_ = 0;
        } else {
            printl("%1: Wrong! Better luck next time!", id());
        }
    } else {
        printl("%1: You were very good in answering my riddle. Fantastic.", id());
        printl("    Now go on to finish your adventure!");
    }
}

} // namespace kd

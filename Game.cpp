#include "Game.h"

#include "Actor.h"
#include "Enemy.h"
#include "Environment.h"
#include "Exit.h"
#include "Item.h"
#include "Input.h"
#include "Player.h"
#include "Print.h"
#include "Random.h"

#include <fstream>
#include <iomanip>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace kd {

Game::Game() : hour_(0)
{
    load("Game.txt");
}

void Game::play()
{
    printl(intro_);
    input::line("");

    printl("Type 'help' for a list of available actions.");

    while (true) {

        if (player()->dead()) {
            printl("I'm sorry, you died :(");
            break;
        }

        if (player()->environment()->id() == "freedom") {
            printl("Congratulations, you finished the game!");
            break;
        }

        std::string line = input::line();
        std::istringstream in(line);
        std::string verb;

        in >> verb;

        if (verb == "look") {
            std::string keyword;
            in >> keyword;
            look(keyword);
        } else if (verb == "hit") {
            std::string enemyId;
            in >> enemyId;
            hit(enemyId);
        } else if (verb == "talk") {
            std::string actorId;
            in >> actorId;
            talk(actorId);
        } else if (verb == "go") {
            std::string direction;
            in >> direction;
            go(direction);
        } else if (verb == "pickup") {
            std::string itemId;
            in >> itemId;
            pickup(itemId);
        } else if (verb == "drop") {
            std::string itemId;
            in >> itemId;
            drop(itemId);
        } else if (verb == "eat") {
            std::string itemId;
            in >> itemId;
            eat(itemId);
        } else if (verb == "status") {
            status();
        } else if (verb == "help") {
            printl(help_);
        } else if (verb == "quit") {
            printl("Hope to see you try again soon!");
            break;
        } else {
            printl("Unknown action");
            printl(help_);
        }
    }

    input::clear();
}

Game::Time Game::time() const
{
    return (hour_ % 24) > 7 ? ((hour_ % 24) > 15 ? Night : Day) : Morning;
}

std::shared_ptr<Environment> Game::environment(std::string id) const
{
    return environments_.at(id);
}

std::shared_ptr<Player> Game::player() const
{
    return player_;
}

void Game::look(std::string keyword) const
{
    if (keyword.empty()) {
        printl("It is %1.", time());
        printl("You're in a %1.", player()->environment()->description());
        if (!player()->environment()->items().empty()) {
            printl("On the floor you see:");
            for (const auto& item : player()->environment()->items()) {
                printl("  %1: %2.", item->id(), item->description());
            }
        }
        if (!player()->environment()->enemies().empty() ||
                !player()->environment()->actors().empty()) {
            printl("In front of you is:");
            for (const auto& enemy : player()->environment()->enemies()) {
                printl("  %1: %2.", enemy->id(), enemy->description());
            }
            for (const auto& actor : player()->environment()->actors()) {
                printl("  %1: %2.", actor->id(), actor->description());
            }
        }
        for (const auto& direction : player()->environment()->visibleDirections()) {
            const auto& exit = player()->environment()->exit(direction);
            printl("To the %1 is a %2.", direction, exit->description());
        }
    } else if (const auto& item = player()->environment()->item(keyword)) {
        printl(item->detailedDescription());
    } else if (const auto& item = player()->item(keyword)) {
        printl(item->detailedDescription());
    } else if (player()->environment()->visibleDirections().count(keyword)) {
        const auto& exit = player()->environment()->exit(keyword);
        printl("To the %1 is a %2.", exit->direction(), exit->description());
        printl(exit->detailedDescription());
    } else if (const auto& enemy = player()->environment()->enemy(keyword)) {
        printl(enemy->detailedDescription());
    } else if (const auto& actor = player()->environment()->actor(keyword)) {
        printl(actor->detailedDescription());
    } else {
        printl("You see nothing of interest.");
    }
}

void Game::hit(std::string enemyId)
{
    const auto& enemy = player()->environment()->enemy(enemyId);

    if (enemy) {
        if (player()->hitRate() > random::probability()) {
            enemy->inflict(player()->damage());
            if (enemy->isDead()) {
                printl("You killed %1!", enemy->id());
                player()->environment()->removeEnemy(enemyId);
            } else {
                printl("You hit %1, who lost %2 HP.", enemyId, player()->damage());
            }
        } else {
            printl("You missed!");
        }
    } else {
        printl("There's no such enemy. You hit into thin air!");
    }

    for (const auto& enemy : player()->environment()->enemies()) {
        enemy->act();
    }
}

void Game::talk(std::string actorId)
{
    std::shared_ptr<Actor> actor;
    if ((actor = player()->environment()->actor(actorId)) ||
            (actor = player()->environment()->enemy(actorId))) {
        actor->talk();
    } else {
        printl("Nothing like that to talk to around here.");
    }
}

void Game::go(std::string direction)
{
    if (!player()->environment()->enemies().empty()) {
        printl("You must defeat all enemies before leaving!");
        return;
    }

    const auto& exit = player()->environment()->exit(direction);

    if (!exit) {
        printl("There's nowhere to go in that direction.");
        return;
    }

    const auto& destination = exit->destination();

    if (player()->environment()->leave() && exit->open() && destination->enter()) {
        if (!exit->visible()) {
            printl("You found a hidden passage!");
        }
        printl("You enter %1.", destination->description());
        player()->move(destination);
        tick();

        if (destination->exits().empty()) {
            printl("The door disappears into thin air behind you.");
            printl("There's no way out, you're trapped!");
            player()->kill();
            return;
        }

        for (const auto& actor : player()->environment()->actors()) {
            actor->act();
        }
    }
}

void Game::pickup(std::string itemId)
{
    if (!player()->environment()->enemies().empty()) {
        printl("You must defeat all enemies before picking anything up!");
        return;
    }

    const auto& item = player()->environment()->removeItem(itemId);

    if (item) {
        player()->addItem(item);
        printl("You picked up the %1.", item->description());
    } else {
        printl("There's no such item to pick up.");
    }
}

void Game::drop(std::string itemId)
{
    if (!player()->environment()->enemies().empty()) {
        printl("You must defeat all enemies before dropping anything!");
        return;
    }

    const auto& item = player()->removeItem(itemId);

    if (item) {
        player()->environment()->addItem(item);
        printl("You dropped %1.", item->id());
    } else {
        printl("You're not carrying such a thing.");
    }
}

void Game::eat(std::string itemId)
{
    if (!player()->environment()->enemies().empty()) {
        printl("You must defeat all enemies before eating anything!");
        return;
    }

    if (const auto& item = player()->item(itemId)) {
        if (item->nutrition()) {
            player()->inflict(-item->nutrition());
            player()->removeItem(itemId);

            printl("You ate %1 and gained %2 HP.", itemId, item->nutrition());
            printl("Your current HP is %1.", player()->hp());
        } else {
            printl("%1 is not edible.", item->description());
        }
    } else {
        printl("There's no such thing in your inventory to eat.");
    }
}

void Game::status() const
{
    printl("Your current HP is %1", player()->hp());
    printl("Your current protection is %1%", 100.0 - 100.0 / player()->protection());
    printl("You can make %1 HP damage.", player()->damage());

    if (!player()->items().empty()) {
        printl("You are carrying:");
        for (const auto& item : player()->items()) {
            printl("  %1: %2.", item->id(), item->description());
        }
    } else {
        printl("You are not carrying anything.");
    }
}

void Game::load(std::string filename)
{
    std::ifstream in(filename);

    in >> std::quoted(intro_) >> std::quoted(help_);

    int numEnvironments;
    in >> numEnvironments;
    for (int i = 0; i < numEnvironments; ++i) {
        const auto& environment = Environment::load(this, in);
        environments_[environment->id()] = environment;
    }

    int numExits;
    in >> numExits;
    for (int i = 0; i < numExits; ++i) {
        const auto& exit = Exit::load(this, in);
        exit->source()->addExit(exit);
    }

    player_ = std::make_shared<Player>(this, in);
}

void Game::tick()
{
    ++hour_;
}

std::ostream& operator<<(std::ostream& out, const Game::Time& time) {
    if (time == Game::Morning) {
        return out << "morning";
    } else if (time == Game::Day) {
        return out << "day";
    } else if (time == Game::Night) {
        return out << "night";
    } else {
        throw std::runtime_error("unknown time value");
    }
}

} // namespace kd

#include "Environment.h"

#include "Actor.h"
#include "Enemy.h"
#include "Exit.h"
#include "Item.h"
#include "Room.h"
#include "Swamp.h"

#include <iomanip>
#include <stdexcept>
#include <utility>

namespace kd {

class Game;

Environment::Environment(Game* game, std::istream& in) : game_(game)
{
    in >> id_;
    in >> std::quoted(description_);

    int numItems;
    in >> numItems;
    for (int i = 0; i < numItems; ++i) {
        addItem(std::make_shared<Item>(in));
    }

    int numActors;
    in >> numActors;
    for (int i = 0; i < numActors; ++i) {
        addActor(Actor::load(game, in));
    }

    int numEnemies;
    in >> numEnemies;
    for (int i = 0; i < numEnemies; ++i) {
        addEnemy(Enemy::load(game, in));
    }
}

Environment::~Environment()
{
}

Game* Environment::game()
{
    return game_;
}

std::string Environment::id() const
{
    return id_;
}

std::string Environment::description() const
{
    return description_;
}

std::shared_ptr<Exit> Environment::exit(std::string direction) const
{
    return exits_.count(direction) ? exits_.at(direction) : std::shared_ptr<Exit>();
}

void Environment::addExit(std::shared_ptr<Exit> exit)
{
    exits_.insert({ exit->direction(), exit });
}

std::vector<std::shared_ptr<Exit>> Environment::exits() const
{
    std::vector<std::shared_ptr<Exit>> exits;
    for (const auto& entry : exits_) {
        exits.push_back(entry.second);
    }
    return exits;
}

std::set<std::string> Environment::availableDirections() const
{
    std::set<std::string> directions;
    for (const auto& entry : exits_) {
        directions.insert(entry.first);
    }
    return directions;
}

std::set<std::string> Environment::visibleDirections() const
{
    std::set<std::string> directions;
    for (const auto& entry : exits_) {
        if (entry.second->visible()) {
            directions.insert(entry.first);
        }
    }
    return directions;
}

std::shared_ptr<Item> Environment::item(std::string itemId) const
{
    return items_.count(itemId) ? items_.at(itemId) : std::shared_ptr<Item>();
}

void Environment::addItem(std::shared_ptr<Item> item)
{
    items_.insert({ item->id(), item });
}

std::shared_ptr<Item> Environment::removeItem(std::string itemId)
{
    const auto& removedItem = item(itemId);
    if (removedItem) {
        items_.erase(removedItem->id());
    }
    return removedItem;
}

std::vector<std::shared_ptr<Item>> Environment::items() const
{
    std::vector<std::shared_ptr<Item>> items;
    for (const auto& entry : items_) {
        items.push_back(entry.second);
    }
    return items;
}

std::shared_ptr<Actor> Environment::actor(std::string actorId) const
{
    return actors_.count(actorId) ? actors_.at(actorId) : std::shared_ptr<Actor>();
}

void Environment::addActor(std::shared_ptr<Actor> actor)
{
    actors_.insert({ actor->id(), actor });
}

std::shared_ptr<Actor> Environment::removeActor(std::string actorId)
{
    const auto& removedActor = actor(actorId);
    if (removedActor) {
        actors_.erase(removedActor->id());
    }
    return removedActor;
}

std::vector<std::shared_ptr<Actor>> Environment::actors() const
{
    std::vector<std::shared_ptr<Actor>> actors;
    for (const auto& entry : actors_) {
        actors.push_back(entry.second);
    }
    return actors;
}

std::shared_ptr<Enemy> Environment::enemy(std::string enemyId) const
{
    return enemies_.count(enemyId) ? enemies_.at(enemyId) : std::shared_ptr<Enemy>();
}

void Environment::addEnemy(std::shared_ptr<Enemy> enemy)
{
    enemies_.insert({ enemy->id(), enemy });
}

std::shared_ptr<Enemy> Environment::removeEnemy(std::string enemyId)
{
    const auto& removedEnemy = enemy(enemyId);
    if (removedEnemy) {
        enemies_.erase(removedEnemy->id());
    }
    return removedEnemy;
}

std::vector<std::shared_ptr<Enemy>> Environment::enemies() const
{
    std::vector<std::shared_ptr<Enemy>> enemies;
    for (const auto& entry : enemies_) {
        enemies.push_back(entry.second);
    }
    return enemies;
}

std::shared_ptr<Environment> Environment::load(Game* game, std::istream &in)
{
    std::string type;
    in >> type;

    if (type == "Room") {
        return std::make_shared<Room>(game, in);
    } else if (type == "Swamp") {
        return std::make_shared<Swamp>(game, in);
    } else {
        throw std::runtime_error("Unknown environment type " + type);
    }
}

std::ostream& operator<<(std::ostream& out, const Environment& environment)
{
    return out << environment.description();
}

} // namespace kd

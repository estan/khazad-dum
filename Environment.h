#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

namespace kd {

class Actor;
class Enemy;
class Exit;
class Game;
class Item;

class Environment
{
public:
    Environment(Game *game, std::istream& in);
    virtual ~Environment();

    Game* game();

    std::string id() const;
    std::string description() const;

    // Exits
    std::shared_ptr<Exit> exit(std::string direction) const;
    void addExit(std::shared_ptr<Exit> exit);
    std::vector<std::shared_ptr<Exit>> exits() const;

    std::set<std::string> availableDirections() const;
    std::set<std::string> visibleDirections() const;

    // Items
    std::shared_ptr<Item> item(std::string itemId) const;
    void addItem(std::shared_ptr<Item> item);
    std::shared_ptr<Item> removeItem(std::string itemId);
    std::vector<std::shared_ptr<Item>> items() const;

    // Actors
    std::shared_ptr<Actor> actor(std::string actorId) const;
    void addActor(std::shared_ptr<Actor> actor);
    std::shared_ptr<Actor> removeActor(std::string actorId);
    std::vector<std::shared_ptr<Actor>> actors() const;

    // Enemies
    std::shared_ptr<Enemy> enemy(std::string enemyId) const;
    void addEnemy(std::shared_ptr<Enemy> enemy);
    std::shared_ptr<Enemy> removeEnemy(std::string enemyId);
    std::vector<std::shared_ptr<Enemy>> enemies() const;

    virtual bool enter() = 0;
    virtual bool leave() = 0;

    static std::shared_ptr<Environment> load(Game* game, std::istream& in);

private:
    Game* game_;

    std::string id_;
    std::string description_;

    std::map<std::string, std::shared_ptr<Exit>> exits_;
    std::map<std::string, std::shared_ptr<Item>> items_;
    std::map<std::string, std::shared_ptr<Actor>> actors_;
    std::map<std::string, std::shared_ptr<Enemy>> enemies_;
};

std::ostream& operator<<(std::ostream& out, const Environment& environment);

} // namespace kd

#endif // ENVIRONMENT_H

#ifndef PLAYER_H
#define PLAYER_H

#include <istream>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace kd {

class Environment;
class Game;
class Item;

class Player
{
public:
    explicit Player(Game* game, std::istream& in);

    int hp() const;
    void inflict(int damage);
    void kill();
    bool dead() const;
    int damage() const;
    int protection() const;
    double hitRate() const;

    std::shared_ptr<Environment> environment() const;

    void move(std::shared_ptr<Environment> environment);

    std::shared_ptr<Item> item(std::string itemId) const;
    void addItem(std::shared_ptr<Item> item);
    std::shared_ptr<Item> removeItem(std::string itemId);
    std::vector<std::shared_ptr<Item>> items() const;

private:
    Game* game_;

    int hp_;

    std::shared_ptr<Environment> environment_;
    std::map<std::string, std::shared_ptr<Item>> items_;
};

} // namespace kd

#endif // PLAYER_H

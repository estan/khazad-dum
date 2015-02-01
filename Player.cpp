#include "Player.h"

#include "Game.h"
#include "Item.h"

#include <algorithm>
#include <stdexcept>
#include <utility>

namespace kd {

Player::Player(Game* game, std::istream& in) : game_(game)
{
    std::string type;
    in >> type;
    if (type != "Player") {
        throw std::runtime_error("Unknown player type " + type);
    }

    in >> hp_;

    std::string environmentId;
    in >> environmentId;
    move(game_->environment(environmentId));
}

int Player::hp() const
{
    return hp_;
}

void Player::inflict(int damage)
{
    hp_ -= damage;
}

void Player::kill()
{
    hp_ = 0;
}

bool Player::dead() const
{
    return hp() <= 0;
}

int Player::damage() const
{
    int maxDamage = 1;

    for (const auto& item : items()) {
        if (item->damage() > maxDamage) {
            maxDamage = item->damage();
        }
    }
    return maxDamage;
}

int Player::protection() const
{
    int maxProtection = 1;

    for (const auto& item : items()) {
        if (item->protection() > maxProtection) {
            maxProtection = item->protection();
        }
    }
    return maxProtection;
}

double Player::hitRate() const
{
    return std::max(0.5, hp() > 100 ? 1.0 : hp() / 100.0);
}

std::shared_ptr<Environment> Player::environment() const
{
    return environment_;
}

void Player::move(std::shared_ptr<Environment> environment)
{
    environment_ = environment;
}

std::shared_ptr<Item> Player::item(std::string itemId) const
{
    return items_.count(itemId) ? items_.at(itemId) : std::shared_ptr<Item>();
}

void Player::addItem(std::shared_ptr<Item> item)
{
    items_.insert({ item->id(), item });
}

std::shared_ptr<Item> Player::removeItem(std::string itemId)
{
    const auto& removedItem = item(itemId);
    if (removedItem) {
        items_.erase(removedItem->id());
    }
    return removedItem;
}

std::vector<std::shared_ptr<Item>> Player::items() const
{
    std::vector<std::shared_ptr<Item>> items;
    for (const auto& entry : items_) {
        items.push_back(entry.second);
    }
    return items;
}

} // namespace kd

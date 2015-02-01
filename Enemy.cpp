#include "Enemy.h"

#include "Balrog.h"
#include "Game.h"
#include "Goblin.h"
#include "Orc.h"
#include "Player.h"
#include "Print.h"
#include "Random.h"

#include <stdexcept>
#include <string>

namespace kd {

Enemy::Enemy(Game* game, std::istream& in) : Actor(game, in)
{
    in >> hp_;
    in >> damage_;
    in >> hitRate_;
}

Enemy::~Enemy()
{
}

int Enemy::hp() const
{
    return hp_;
}

void Enemy::inflict(int damage)
{
    hp_ -= damage;
}

bool Enemy::isDead() const
{
    return hp() <= 0;
}

int Enemy::damage() const
{
    return damage_;
}

double Enemy::hitRate() const
{
    return hitRate_;
}

void Enemy::act()
{
    int realDamage = damage() / game()->player()->protection();

    if (hitRate() > random::probability()) {
        game()->player()->inflict(realDamage);

        printl("You were hit by %1, losing %2 HP.", id(), realDamage);
        printl("You have %1 HP left.", game()->player()->hp());
    } else {
        printl("%1 took a swing, but missed!", id());
    }
}

void Enemy::talk()
{
    printl("The %1 is not interested in talking!", description());
}

std::shared_ptr<Enemy> Enemy::load(Game* game, std::istream& in)
{
    std::string type;
    in >> type;

    if (type == "Balrog") {
        return std::make_shared<Balrog>(game, in);
    } else if (type == "Goblin") {
        return std::make_shared<Goblin>(game, in);
    } else if (type == "Orc") {
        return std::make_shared<Orc>(game, in);
    } else {
        throw std::runtime_error("Unknown enemy type " + type);
    }
}

} // namespace kd

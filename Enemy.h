#ifndef ENEMY_H
#define ENEMY_H

#include "Actor.h"

#include <istream>
#include <memory>

namespace kd {

class Game;

class Enemy : public Actor
{
public:
    Enemy(Game* game, std::istream& in);
    virtual ~Enemy();

    int hp() const;
    void inflict(int damage);
    bool isDead() const;
    int damage() const;
    double hitRate() const;

    virtual void act() override;
    virtual void talk() override;

    static std::shared_ptr<Enemy> load(Game* game, std::istream& in);

private:
    int hp_;
    int damage_;
    double hitRate_;
};

} // namespace kd

#endif // ENEMY_H

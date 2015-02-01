#ifndef ACTOR_H
#define ACTOR_H

#include <istream>
#include <memory>
#include <string>

namespace kd {

class Game;

class Actor
{
public:
    Actor(Game* game, std::istream& in);
    virtual ~Actor();

    std::string id() const;
    std::string description() const;
    std::string detailedDescription() const;

    virtual void act() = 0;
    virtual void talk() = 0;

    static std::shared_ptr<Actor> load(Game* game, std::istream& in);

protected:
    Game* game() const;

private:
    Game* game_;

    std::string id_;
    std::string description_;
    std::string detailedDescription_;
};

} // namespace kd

#endif // ACTOR_H

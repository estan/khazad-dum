#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <map>
#include <memory>
#include <string>

namespace kd {

class Environment;
class Player;

class Game
{
public:
    enum Time {
        Morning,
        Day,
        Night
    };

public:
    Game();

    void play();

    Time time() const;

    std::shared_ptr<Environment> environment(std::string id) const;
    std::shared_ptr<Player> player() const;

private:
    void look(std::string keyword) const;
    void hit(std::string enemyId);
    void talk(std::string actorId);
    void go(std::string direction);
    void pickup(std::string itemId);
    void drop(std::string itemId);
    void eat(std::string itemId);
    void status() const;

private:
    void load(std::string filename);
    void tick();

private:
    std::shared_ptr<Player> player_;
    std::map<std::string, std::shared_ptr<Environment>> environments_;

    std::string intro_;
    std::string help_;

    int hour_;
};

std::ostream& operator<<(std::ostream& out, const Game::Time& time);

} // namespace kd

#endif // GAME_H

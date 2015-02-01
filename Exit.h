#ifndef EXIT_H
#define EXIT_H

#include <iostream>
#include <memory>
#include <string>

namespace kd {

class Environment;
class Game;

class Exit
{
public:
    Exit(Game* game, std::istream& in);
    virtual ~Exit();

    std::string description() const;
    std::string detailedDescription() const;
    std::string direction() const;
    std::shared_ptr<Environment> source() const;
    std::shared_ptr<Environment> destination() const;

    virtual bool open() = 0;
    virtual bool visible() const = 0;

    static std::shared_ptr<Exit> load(Game* game, std::istream& in);

protected:
    virtual std::string destinationId() const = 0;

    Game* game() const;

private:
    Game* game_;

    std::string description_;
    std::string detailedDescription_;
    std::string direction_;
    std::string sourceId_;
};

std::ostream& operator<<(std::ostream& out, const Exit& exit);

} // namespace kd

#endif // EXIT_H

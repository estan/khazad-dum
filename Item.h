#ifndef ITEM_H
#define ITEM_H

#include <istream>
#include <string>

namespace kd {

class Item
{
public:
    explicit Item(std::istream& in);

    std::string id() const;
    std::string description() const;
    std::string detailedDescription() const;

    int damage() const;
    int protection() const;
    int nutrition() const;

private:
    std::string id_;
    std::string description_;
    std::string detailedDescription_;

    int damage_;
    int protection_;
    int nutrition_;
};

} // namespace kd

#endif // ITEM_H

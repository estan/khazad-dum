#ifndef PRINT_H
#define PRINT_H

#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <utility>

namespace kd {

namespace {

std::string formatted(const std::string& format, const size_t)
{
    return format;
}

template <typename T, typename... Args>
std::string formatted(const std::string& format, const size_t i, T&& val, Args&&...args)
{
    std::regex pattern("%" + std::to_string(i));
    std::ostringstream os;
    os << val;
    return formatted(std::regex_replace(format, pattern, os.str()), i + 1, std::forward<Args>(args)...);
}

} // namespace

template <typename... Args>
inline void print(const std::string &format, Args &&...args)
{
    std::cout << formatted(format, 1, std::forward<Args>(args)...);
}

template <typename... Args>
inline void printl(const std::string &format, Args &&...args)
{
    std::cout << formatted(format, 1, std::forward<Args>(args)...) << std::endl;
}

} // namespace kd

#endif // PRINT_H


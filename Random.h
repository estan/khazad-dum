#ifndef RANDOM_H
#define RANDOM_H

#include <random>

namespace kd {

namespace random {

std::default_random_engine& engine();
double probability();

} // namespace random

} // namespace kd

#endif // RANDOM_H


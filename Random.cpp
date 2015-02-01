#include "Random.h"

namespace kd {

namespace random {

namespace {
    static std::random_device random_device;
    static std::default_random_engine random_engine(random_device());
    static std::uniform_real_distribution<double> one_to_zero(0.0, 1.0);
} // namespace

std::default_random_engine& engine()
{
    return random_engine;
}

double probability()
{
    return one_to_zero(engine());
}

} // namespace random

} // namespace kd

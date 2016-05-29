#include "Random.h"

using namespace ME;


MEInt64 Random::get(MEInt64 from, MEInt64 to) {
    std::random_device generator;
    std::uniform_int_distribution<MEInt64> dist(from, to);
    return dist(generator);
}

MEInt64 Random::get(MEInt64 to) {
    std::random_device generator;
    std::uniform_int_distribution<MEInt64> dist(0, to);
    return dist(generator);
}
#include "Random.h"

using namespace ME;

std::atomic<uint64> Random::unique_id = {0};

uint64 Random::get(uint64 from, uint64 to) {
    std::random_device generator;
    std::uniform_int_distribution<uint64> dist(from, to);
    return dist(generator);
}

uint64 Random::get(uint64 to) {
    std::random_device generator;
    std::uniform_int_distribution<uint64> dist(0, to);
    return dist(generator);
}


uint64 Random::unique() {
	return Random::unique_id++;
}
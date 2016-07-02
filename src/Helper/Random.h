#ifndef RANDOM_H
#define RANDOM_H
#include <random>
#include <atomic>

#include "Helper/BasicTypes.h"

namespace ME {

class Random {
public:
    static uint64 get(uint64 from, uint64 to);
    static uint64 get(uint64 to);
    static uint64 unique();

private:
    static std::atomic<uint64> unique_id;
};

}

#endif // RANDOM_H

#ifndef RANDOM_H
#define RANDOM_H
#include <random>
#include "Helper/Types.h"

namespace ME {

class Random {
public:
    static MEInt64 get(MEInt64 from, MEInt64 to);
    static MEInt64 get(MEInt64 to);
};

}

#endif // RANDOM_H

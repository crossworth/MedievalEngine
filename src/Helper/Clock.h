#ifndef CLOCK_H
#define CLOCK_H
#include <SFML/System/Clock.hpp>
#include "Helper/Types.h"


namespace ME {

class Clock {
public:
    Clock();
    void restart();

    float getSeconds();
    uint32 getMilliSeconds();
    uint64 getMicroSeconds();

    static uint64 getMicroSeconds(const float &time);
    static uint32 getMilliSeconds(const float &time);
    static uint32 getMilliSeconds(const uint64 &time);
    static float getSeconds(const uint64 &time);
private:
    sf::Clock mClock;
};

}

#endif // CLOCK_H

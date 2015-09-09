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
    MEUInt32 getMilliSeconds();
    MEUInt64 getMicroSeconds();

    static MEUInt64 getMicroSeconds(const float& time);
    static MEUInt32 getMilliSeconds(const float& time);
    static MEUInt32 getMilliSeconds(const MEUInt64& time);
    static float getSeconds(const MEUInt64& time);
private:
    sf::Clock mClock;
};

}

#endif // CLOCK_H

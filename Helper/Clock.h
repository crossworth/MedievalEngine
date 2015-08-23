#ifndef CLOCK_H
#define CLOCK_H
#include <SFML/System/Clock.hpp>


namespace ME {

class Clock {
public:
    Clock();
    void restart();

    // Default time is miliseconds
    unsigned int getTime();
private:
    sf::Clock mClock;
};

}

#endif // CLOCK_H

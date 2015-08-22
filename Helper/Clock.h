#ifndef CLOCK_H
#define CLOCK_H
#include <SFML/System/Clock.hpp>


namespace ME {

class Clock {
public:
    Clock();
    void restart();
    // Retorna o tempo em milesegundos
    long long int getTime();
private:
    sf::Clock mClock;
};

}

#endif // CLOCK_H

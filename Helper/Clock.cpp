#include "Clock.h"

using namespace ME;

Clock::Clock() {
    restart();
}

void Clock::restart() {
    mClock.restart();
}

unsigned int Clock::getTime() {
    return mClock.getElapsedTime().asMilliseconds();
}


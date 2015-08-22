#include "Clock.h"

using namespace ME;

Clock::Clock() {
    restart();
}

void Clock::restart() {
    mClock.restart();
}

long long Clock::getTime() {
    return mClock.getElapsedTime().asMilliseconds();
}


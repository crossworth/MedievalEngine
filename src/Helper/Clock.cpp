#include "Clock.h"

using namespace ME;

Clock::Clock() {
    restart();
}

void Clock::restart() {
    mClock.restart();
}

float Clock::getSeconds() {
    return mClock.getElapsedTime().asSeconds();
}

uint32 Clock::getMilliSeconds() {
    return mClock.getElapsedTime().asMilliseconds();
}

uint64 Clock::getMicroSeconds() {
    return mClock.getElapsedTime().asMicroseconds();
}

float Clock::getSeconds(const uint64 &time) {
    return sf::microseconds(time).asSeconds();
}

uint64 Clock::getMicroSeconds(const float &time) {
    return sf::seconds(time).asMicroseconds();
}

uint32 Clock::getMilliSeconds(const float &time) {
    return sf::seconds(time).asMilliseconds();
}

uint32 Clock::getMilliSeconds(const uint64 &time) {
    return sf::microseconds(time).asMilliseconds();
}

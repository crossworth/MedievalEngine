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

MEUInt32 Clock::getMilliSeconds() {
    return mClock.getElapsedTime().asMilliseconds();
}

MEUInt64 Clock::getMicroSeconds() {
    return mClock.getElapsedTime().asMicroseconds();
}

float Clock::getSeconds(const MEUInt64& time) {
    return sf::microseconds(time).asSeconds();
}

MEUInt64 Clock::getMicroSeconds(const float& time) {
    return sf::seconds(time).asMicroseconds();
}

MEUInt32 Clock::getMilliSeconds(const float& time) {
    return sf::seconds(time).asMilliseconds();
}

MEUInt32 Clock::getMilliSeconds(const MEUInt64& time) {
    return sf::microseconds(time).asMilliseconds();
}

#include "Effects.h"

using namespace ME;

Effects::Effects() : mDone(false) {

}

void Effects::setDone() {
    mDone = true;
}

std::string Effects::getType() {
    return mType;
}

void Effects::resetClock() {
    mClock.restart();
}

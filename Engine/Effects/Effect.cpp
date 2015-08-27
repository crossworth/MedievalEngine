#include "Effect.h"

using namespace ME;

Effect::Effect() : mDone(false) {

}

void Effect::setDone() {
    LOG << Log::VERBOSE
    << "[Effect::setDone] Effect " + getTypeStd() + " done"
    << std::endl;

    mDone = true;
    mCallback();
}

bool Effect::isDone() {
    return mDone;
}

Effect::Type Effect::getType() {
    return mType;
}

std::string Effect::getTypeStd() {
    switch(mType) {
    case Type::FADE:
        return "fade";
        break;
    case Type::STROBE:
        return "strobe";
        break;
    default:
        return "unkonw";
        break;
    }
}

void Effect::restartClock() {
    mClock.restart();
}

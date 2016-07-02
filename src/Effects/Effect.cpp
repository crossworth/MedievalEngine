#include "Effect.h"

using namespace ME;

Effect::Effect() : mDone(false) {

}

void Effect::setDone() {
    LOG << Log::VERBOSE
    << "[Effect::setDone] Effect " + getTypeStr() + " done"
    << std::endl;

    mDone = true;

    // We call our Callback function after the effect it's done
    mCallback();
}

bool Effect::isDone() {
    return mDone;
}

Effect::Type Effect::getType() {
    return mType;
}

std::string Effect::getTypeStr() {
    switch(mType) {
    case Type::FADE:
        return "Fade";
        break;
    case Type::STROBE:
        return "Strobe";
        break;
    case Type::SHADER:
        return "Shader";
        break;
    default:
        return "Unkonw";
        break;
    }
}

void Effect::restartClock() {
    mClock.restart();
}

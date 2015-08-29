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

void Effect::registerRenderStates(sf::RenderStates* states) {
    mRenderStates = states;
}

Effect::Type Effect::getType() {
    return mType;
}

std::string Effect::getTypeStd() {
    switch(mType) {
    case Type::FADE:
        return "Fade";
        break;
    case Type::STROBE:
        return "Strobe";
        break;
    case Type::BLUR:
        return "Blur";
        break;
    default:
        return "Unkonw";
        break;
    }
}

void Effect::restartClock() {
    mClock.restart();
}

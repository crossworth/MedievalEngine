#include "Effects.h"

using namespace ME;

Effects::Effects() : m_done(false) {

}

void Effects::setDone() {
    m_done = true;
}

Effects::EffectType Effects::getType() {
    return m_type;
}

std::string Effects::getTypeStd() {
    switch(m_type) {
    case EffectType::FADE:
        return "fade";
        break;
    case EffectType::STROBE:
        return "strobe";
        break;
    }

    return "unkonw";
}

void Effects::resetClock() {
    mClock.restart();
}

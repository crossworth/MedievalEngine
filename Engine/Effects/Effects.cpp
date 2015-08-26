#include "Effects.h"

using namespace ME;

Effects::Effects() : m_done(false) {

}

void Effects::setDone() {
    m_done = true;
}

Effects::Type Effects::getType() {
    return m_type;
}

std::string Effects::getTypeStd() {
    switch(m_type) {
    case Type::FADE:
        return "fade";
        break;
    case Type::STROBE:
        return "strobe";
        break;
    }

    return "unkonw";
}

void Effects::resetClock() {
    mClock.restart();
}

#include "Audible.h"

using namespace ME;

float Audible::VOLUME         = ME::ENGINE_DEFAULTS::DEFAULT_VOLUME;
float Audible::VOICE_VOLUME   = ME::ENGINE_DEFAULTS::VOICE_VOLUME;
float Audible::MUSIC_VOLUME   = ME::ENGINE_DEFAULTS::MUSIC_VOLUME;
float Audible::AMBIENT_VOLUME = ME::ENGINE_DEFAULTS::AMBIENT_VOLUME;

Audible::Audible() {

}

AudioType Audible::getType() {
    return mType;
}

void Audible::setType(const AudioType& type) {
    mType = type;
}

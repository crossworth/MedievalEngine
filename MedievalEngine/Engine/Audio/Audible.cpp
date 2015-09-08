#include "Audible.h"

using namespace ME;

// Rename the VOLUE -> GLOBAL_VOLUME
float Audible::VOLUME         = ME::ENGINE_DEFAULTS::DEFAULT_VOLUME;
float Audible::VOICE_VOLUME   = ME::ENGINE_DEFAULTS::VOICE_VOLUME;
float Audible::MUSIC_VOLUME   = ME::ENGINE_DEFAULTS::MUSIC_VOLUME;
float Audible::AMBIENT_VOLUME = ME::ENGINE_DEFAULTS::AMBIENT_VOLUME;

Audible::Audible() {

}

AudioType Audible::getType() {
    return mAudioType;
}

void Audible::setType(const AudioType& type) {
    mAudioType = type;
}

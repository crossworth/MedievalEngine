#include "Audible.h"
#include "Resources/ResourceManager.h"

using namespace ME;

// Initialize the value with the engine default's
float Audible::GLOBAL_VOLUME  = ME::ENGINE_DEFAULTS::DEFAULT_VOLUME;
float Audible::VOICE_VOLUME   = ME::ENGINE_DEFAULTS::VOICE_VOLUME;
float Audible::MUSIC_VOLUME   = ME::ENGINE_DEFAULTS::MUSIC_VOLUME;
float Audible::AMBIENT_VOLUME = ME::ENGINE_DEFAULTS::AMBIENT_VOLUME;

Audible::Audible() {
    
}

Audio::AudioType Audible::getType() {
    return mAudioType;
}

void Audible::setType(const Audio::AudioType& type) {
    mAudioType = type;
}

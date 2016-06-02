#include "Sound.h"

using namespace ME;

Sound::Sound(const std::string &fileName, const Audio::AudioType& type) {
    mType = Resource::Type::SOUND;

    loadFromFile(fileName, type);
}

void Sound::updateVolume() {
    float ratio = static_cast<float>(Audible::GLOBAL_VOLUME * 0.01);

    switch(mAudioType) {
        case Audio::AudioType::VOICE:
            setVolume(Audible::VOICE_VOLUME * ratio);
            break;
        case Audio::AudioType::MUSIC:
            setVolume(Audible::MUSIC_VOLUME * ratio);
            break;
        case Audio::AudioType::AMBIENT:
            setVolume(Audible::AMBIENT_VOLUME * ratio);
            break;
        default:
            setVolume(Audible::GLOBAL_VOLUME);
    }
}

sf::Sound* Sound::loadFromFile(const std::string &fileName, const Audio::AudioType& type) {
    if (!mSoundBuffer.loadFromFile(ENGINE_DEFAULTS::ASSETS_PATH + fileName)) {
        LOG << Log::VERBOSE << "[Sound::loadFromFile] Error while opening sound: "
            << ENGINE_DEFAULTS::ASSETS_PATH + fileName << std::endl;
    }
    mSound.setBuffer(mSoundBuffer);

    setType(type);
    updateVolume();

    return &mSound;
}

sf::Sound* Sound::getResourcePointer() {
    return &mSound;
}

unsigned int Sound::getDuration() {
    return mSound.getBuffer()->getDuration().asMilliseconds();
}

float Sound::getAttenuation() {
    return mSound.getAttenuation();
}

float Sound::getMinDistance() {
    return mSound.getMinDistance();
}

bool Sound::isRelativeToListener() {
    return mSound.isRelativeToListener();
}

Vect3f Sound::getPosition() {
    return Vect3f(mSound.getPosition().x,
                  mSound.getPosition().y,
                  mSound.getPosition().z);
}

float Sound::getVolume() {
    return mSound.getVolume();
}

float Sound::getPitch() {
    return mSound.getPitch();
}

void Sound::setAttenuation(const float &attenuation) {
    mSound.setAttenuation(attenuation);
}

void Sound::setMinDistance(const float &distance) {
    mSound.setMinDistance(distance);
}

void Sound::setRelativeToListener(const bool &relative) {
    mSound.setRelativeToListener(relative);
}

void Sound::setPosition(const Vect3f &pos) {
    mSound.setPosition(pos.x, pos.y, pos.z);
}

void Sound::setVolume(const float &volume) {
    mSound.setVolume(volume);
}

void Sound::setPitch(const float &pitch) {
    mSound.setPitch(pitch);
}

Audio::AudioStatus Sound::getStatus() {
    switch (mSound.getStatus()) {
    case sf::SoundSource::Paused:
        return Audio::AudioStatus::PAUSED;
        break;
    case sf::SoundSource::Playing:
        return Audio::AudioStatus::PLAYING;
        break;
    case sf::SoundSource::Stopped:
        return Audio::AudioStatus::STOPPED;
        break;
    }
    return Audio::AudioStatus::STOPPED;
}

unsigned int Sound::getPlayingOffSet() {
    return mSound.getPlayingOffset().asMilliseconds();
}

void Sound::setPlayingOffSet(const unsigned int offset) {
    mSound.setPlayingOffset(sf::milliseconds(offset));
}

bool Sound::isLoopMode() {
    return mSound.getLoop();
}

void Sound::setLoopMode(const bool& loop) {
    mSound.setLoop(loop);
}

void Sound::play() {
    mSound.play();
}

void Sound::pause() {
    mSound.pause();
}

void Sound::stop() {
    mSound.stop();
}

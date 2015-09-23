#include "Music.h"

using namespace ME;

Music::Music() {
    mType = Resource::Type::MUSIC;
}

bool Music::loadFromFile(const std::string& fileName, const Audio::AudioType& type) {
    if (!mMusic.openFromFile(ENGINE_DEFAULTS::ASSETS_PATH + fileName)) {
        LOG << Log::WARNING << "[Music::loadFromFile] Error while opening music: "
            << ENGINE_DEFAULTS::ASSETS_PATH + fileName
            << std::endl;
    } else {
        mIsValid = true;
    }

    setType(type);

    float ratio = static_cast<float>(Audible::GLOBAL_VOLUME * 0.01);

    switch(type) {
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

    return mIsValid;
}

sf::Music* Music::getResourcePointer() {
    return &mMusic;
}

unsigned int Music::getDuration() {
    return mMusic.getDuration().asMilliseconds();
}

float Music::getAttenuation() {
    return mMusic.getAttenuation();
}

float Music::getMinDistance() {
    return mMusic.getMinDistance();
}

bool Music::isRelativeToListener() {
    return mMusic.isRelativeToListener();
}

Vect3f Music::getPosition() {
    return Vect3f(mMusic.getPosition().x,
                  mMusic.getPosition().y,
                  mMusic.getPosition().z);
}

float Music::getVolume() {
    return mMusic.getVolume();
}

float Music::getPitch() {
    return mMusic.getPitch();
}

void Music::setAttenuation(const float& attenuation) {
    mMusic.setAttenuation(attenuation);
}

void Music::setMinDistance(const float& distance) {
    mMusic.setMinDistance(distance);
}

void Music::setRelativeToListener(const bool& relative) {
    mMusic.setRelativeToListener(relative);
}

void Music::setPosition(const Vect3f& pos) {
    mMusic.setPosition(pos.x, pos.y, pos.z);
}

void Music::setVolume(const float& volume) {
    mMusic.setVolume(volume);
}

void Music::setPitch(const float& pitch) {
    mMusic.setPitch(pitch);
}

Audio::AudioStatus Music::getStatus() {
    switch (mMusic.getStatus()) {
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

unsigned int Music::getPlayingOffSet() {
    return mMusic.getPlayingOffset().asMilliseconds();
}

void Music::setPlayingOffSet(const unsigned int offset) {
    mMusic.setPlayingOffset(sf::milliseconds(offset));
}

bool Music::isLoopMode() {
    return mMusic.getLoop();
}

void Music::setLoopMode(const bool& loop) {
    mMusic.setLoop(loop);
}

void Music::play() {
    mMusic.play();
}

void Music::pause() {
    mMusic.pause();
}

void Music::stop() {
    mMusic.stop();
}

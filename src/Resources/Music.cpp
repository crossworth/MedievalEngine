#include "Music.h"

using namespace ME;

Music::Music() {
    mType = Resource::Type::MUSIC;
}

void Music::updateVolume() {
    float ratio = static_cast<float>(Audible::GLOBAL_VOLUME * 0.01);

    switch(mAudioType) {
        case Audible::AudioType::VOICE:
            setVolume(Audible::VOICE_VOLUME * ratio);
            break;
        case Audible::AudioType::MUSIC:
            setVolume(Audible::MUSIC_VOLUME * ratio);
            break;
        case Audible::AudioType::AMBIENT:
            setVolume(Audible::AMBIENT_VOLUME * ratio);
            break;
        default:
            setVolume(Audible::GLOBAL_VOLUME);
    }
}

bool Music::loadFromFile(const std::string &fileName, const Audible::AudioType &type) {
    if (!mMusic.openFromFile(ENGINE_DEFAULTS::DATA_PATH + fileName)) {
        LOG << Log::WARNING << "[Music::loadFromFile] Error while opening music: "
            << ENGINE_DEFAULTS::DATA_PATH + fileName
            << std::endl;
    } else {
        mIsValid = true;
    }

    setType(type);
    updateVolume();

    return mIsValid;
}

sf::Music* Music::getResourcePointer() {
    return &mMusic;
}

uint32 Music::getDuration() {
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

void Music::setAttenuation(const float &attenuation) {
    mMusic.setAttenuation(attenuation);
}

void Music::setMinDistance(const float &distance) {
    mMusic.setMinDistance(distance);
}

void Music::setRelativeToListener(const bool &relative) {
    mMusic.setRelativeToListener(relative);
}

void Music::setPosition(const Vect3f &pos) {
    mMusic.setPosition(pos.x, pos.y, pos.z);
}

void Music::setVolume(const float &volume) {
    mMusic.setVolume(volume);
}

void Music::setPitch(const float &pitch) {
    mMusic.setPitch(pitch);
}

Audible::AudioStatus Music::getStatus() {
    switch (mMusic.getStatus()) {
    case sf::SoundSource::Paused:
        return Audible::AudioStatus::PAUSED;
        break;
    case sf::SoundSource::Playing:
        return Audible::AudioStatus::PLAYING;
        break;
    case sf::SoundSource::Stopped:
        return Audible::AudioStatus::STOPPED;
        break;
    }
    return Audible::AudioStatus::STOPPED;
}

uint32 Music::getPlayingOffSet() {
    return mMusic.getPlayingOffset().asMilliseconds();
}

void Music::setPlayingOffSet(const uint32 &offset) {
    mMusic.setPlayingOffset(sf::milliseconds(offset));
}

bool Music::isLoopMode() {
    return mMusic.getLoop();
}

void Music::setLoopMode(const bool &loop) {
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

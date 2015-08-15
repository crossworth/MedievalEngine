#include "Sound.h"

using namespace ME;

Sound::Sound(const std::string &fileName) {
    mType = "sound";
    loadFromFile(fileName);
}

sf::Sound* Sound::loadFromFile(const std::string &fileName) {
    if (!mBuffer.loadFromFile(ENGINE_DEFAULTS::ASSETS_PATH + fileName)) {
        LOG << ("[Sound::loadFromFile] Error while opening sound: " + ENGINE_DEFAULTS::ASSETS_PATH + fileName).c_str() << std::endl;
    }
    mSound.setBuffer(mBuffer);
    return &mSound;
}

sf::Sound* Sound::getResourcePointer() {
    return &mSound;
}

sf::Time Sound::getDuration() {
    return mSound.getBuffer()->getDuration();
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
    return Vect3f(mSound.getPosition().x, mSound.getPosition().y, mSound.getPosition().z);
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

AUDIABLE_STATUS Sound::getStatus() {
    switch (mSound.getStatus()) {
    case sf::SoundSource::Paused:
        return PAUSED;
        break;
    case sf::SoundSource::Playing:
        return PLAYING;
        break;
    case sf::SoundSource::Stopped:
        return STOPPED;
        break;
    }
}

sf::Time Sound::getPlayingOffSet() {
    return mSound.getPlayingOffset();
}

void Sound::setPlayingOffSet(const sf::Time &offSet) {
    mSound.setPlayingOffset(offSet);
}

bool Sound::isLoopMode() {
    return mSound.getLoop();
}

void Sound::setLoopMode(const bool &loop) {
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
#include "MusicQueue.h"

#include "Resources/ResourceManager.h"

using namespace ME;

MusicQueue::MusicQueue() {
    mCurrentMusic = mMusics.begin();
    mIsValid      = true;
}

void MusicQueue::insert(const std::string &music) {
    if (ResourceManager::loadMusic(music)) {
        mMusics.push_back(music);
        mCurrentMusic = mMusics.begin();
    }
}

uint32 MusicQueue::getDuration() {
    if (mCurrentMusic != mMusics.end()) {
        return ResourceManager::get<Music>(*mCurrentMusic)->getDuration();
    }
    return 0;
}

float MusicQueue::getAttenuation() {
    if (mCurrentMusic != mMusics.end()) {
        return ResourceManager::get<Music>(*mCurrentMusic)->getAttenuation();
    }
    return 0.0f;
}

float MusicQueue::getMinDistance() {
    if (mCurrentMusic != mMusics.end()) {
        return ResourceManager::get<Music>(*mCurrentMusic)->getMinDistance();
    }
    return 0.0f;
}

bool MusicQueue::isRelativeToListener() {
    if (mCurrentMusic != mMusics.end()) {
        return ResourceManager::get<Music>(*mCurrentMusic)->isRelativeToListener();
    }
    return false;
}

Vect3f MusicQueue::getPosition() {
    if (mCurrentMusic != mMusics.end()) {
        return ResourceManager::get<Music>(*mCurrentMusic)->getPosition();
    }
    return Vect3f(0.0f, 0.0f, 0.0f);
}

float MusicQueue::getVolume() {
    if (mCurrentMusic != mMusics.end()) {
        return ResourceManager::get<Music>(*mCurrentMusic)->getVolume();
    }
    return 0.0f;
}

float MusicQueue::getPitch() {
    if (mCurrentMusic != mMusics.end()) {
        return ResourceManager::get<Music>(*mCurrentMusic)->getPitch();
    }
    return 0.0f;
}

void MusicQueue::setAttenuation(const float &attenuation) {
    if (mCurrentMusic != mMusics.end()) {
        ResourceManager::get<Music>(*mCurrentMusic)->setAttenuation(attenuation);
    }
}

void MusicQueue::setMinDistance(const float &distance) {
    if (mCurrentMusic != mMusics.end()) {
        ResourceManager::get<Music>(*mCurrentMusic)->setMinDistance(distance);
    }
}

void MusicQueue::setRelativeToListener(const bool &relative) {
    if (mCurrentMusic != mMusics.end()) {
        ResourceManager::get<Music>(*mCurrentMusic)->setRelativeToListener(relative);
    }
}

void MusicQueue::setPosition(const Vect3f &pos) {
    if (mCurrentMusic != mMusics.end()) {
        ResourceManager::get<Music>(*mCurrentMusic)->setPosition(pos);
    }
}

void MusicQueue::setVolume(const float &volume) {
    if (mCurrentMusic != mMusics.end()) {
        ResourceManager::get<Music>(*mCurrentMusic)->setVolume(volume);
    }
}

void MusicQueue::updateVolume() {
    for(std::vector<std::string>::iterator it = mMusics.begin(); 
        it != mMusics.end(); it++) {
        ResourceManager::get<Music>(*it)->updateVolume();
    }
}

void MusicQueue::setPitch(const float &pitch) {
    if (mCurrentMusic != mMusics.end()) {
        ResourceManager::get<Music>(*mCurrentMusic)->setPitch(pitch);
    }
}

Audible::AudioStatus MusicQueue::getStatus() {
    return mStatus;
}

uint32 MusicQueue::getPlayingOffSet() {
    if (mCurrentMusic != mMusics.end()) {
        return ResourceManager::get<Music>(*mCurrentMusic)->getPlayingOffSet();
    }
    return 0;
}

void MusicQueue::setPlayingOffSet(const uint32 &offset) {
    if (mCurrentMusic != mMusics.end()) {
        ResourceManager::get<Music>(*mCurrentMusic)->setPlayingOffSet(offset);
    }
}

// We set to play the queue in a random order
// Which don't make much sense since its a QUEUE
// But anyways, its interessant to implement this function
// To our in game music
void MusicQueue::setRandomPlay(const bool &random) {
    mIsRandomPlay = random;
}

bool MusicQueue::isRandomPlay() {
    return mIsRandomPlay;
}

// Here the loop mode works a litte bit different
// We gonna loop all the queue and not only one music
bool MusicQueue::isLoopMode() {
    return mIsLoopMode;
}

void MusicQueue::setLoopMode(const bool &loop) {
    mIsLoopMode = loop;
}

void MusicQueue::play() {
    if (mCurrentMusic != mMusics.end()) {
        mStatus = Audible::AudioStatus::PLAYING;
        ResourceManager::get<Music>(*mCurrentMusic)->play();
    }
}

void MusicQueue::pause() {
    if (mCurrentMusic != mMusics.end()) {
        mStatus = Audible::AudioStatus::PAUSED;
        ResourceManager::get<Music>(*mCurrentMusic)->pause();
    }
}

void MusicQueue::stop() {
    if (mCurrentMusic != mMusics.end()) {
        mStatus = Audible::AudioStatus::STOPPED;
        ResourceManager::get<Music>(*mCurrentMusic)->stop();
    }
}

void MusicQueue::update() {
    if (mCurrentMusic != mMusics.end()) {
        Audible::AudioStatus status = ResourceManager::get<Music>(*mCurrentMusic)->getStatus();

        if (status == Audible::AudioStatus::STOPPED) {
            mStatus = Audible::AudioStatus::STOPPED;
            mCurrentMusic++;

            if (mCurrentMusic == mMusics.end()) {
                if (isRandomPlay()) {
                    std::random_shuffle(mMusics.begin(), mMusics.end());
                }

                mCurrentMusic = mMusics.begin();

                if (isLoopMode()) {
                    play();
                }

            } else {
                play();
            }

            LOG << Log::VERBOSE << "[MusicQueue::update] New track started "
                << std::endl;
        }
    }
}

#include "MusicQueue.h"
#include "Engine/MedievalEngine.h"

using namespace ME;

MusicQueue::MusicQueue() {
    mCurrentMusic = mMusics.begin();
}

void MusicQueue::registerEngine(MedievalEngine* engine) {
    mEngine = engine;
}

void MusicQueue::insert(ResourceID& music) {
    mMusics.push_back(music);

    if (mCurrentMusic == mMusics.end()) {
        mCurrentMusic = mMusics.begin();
    }
}

void MusicQueue::insert(const std::string& music) {
    mMusics.push_back(mEngine->getResourceManager()->loadMusic(music));

    if (mCurrentMusic == mMusics.end()) {
        mCurrentMusic = mMusics.begin();
    }
}

unsigned int MusicQueue::getDuration() {
    return mEngine->getResourceManager()->getResource<Music>(*mCurrentMusic)->getDuration();
}

float MusicQueue::getAttenuation() {
    return mEngine->getResourceManager()->getResource<Music>(*mCurrentMusic)->getAttenuation();
}

float MusicQueue::getMinDistance() {
    return mEngine->getResourceManager()->getResource<Music>(*mCurrentMusic)->getMinDistance();
}

bool MusicQueue::isRelativeToListener() {
    return mEngine->getResourceManager()->getResource<Music>(*mCurrentMusic)->isRelativeToListener();
}

Vect3f MusicQueue::getPosition() {
    return mEngine->getResourceManager()->getResource<Music>(*mCurrentMusic)->getPosition();
}

float MusicQueue::getVolume() {
    return mEngine->getResourceManager()->getResource<Music>(*mCurrentMusic)->getVolume();
}

float MusicQueue::getPitch() {
    return mEngine->getResourceManager()->getResource<Music>(*mCurrentMusic)->getPitch();
}

void MusicQueue::setAttenuation(const float& attenuation) {
    mEngine->getResourceManager()->getResource<Music>(*mCurrentMusic)->setAttenuation(attenuation);
}

void MusicQueue::setMinDistance(const float& distance) {
    mEngine->getResourceManager()->getResource<Music>(*mCurrentMusic)->setMinDistance(distance);
}

void MusicQueue::setRelativeToListener(const bool& relative) {
    mEngine->getResourceManager()->getResource<Music>(*mCurrentMusic)->setRelativeToListener(relative);
}

void MusicQueue::setPosition(const Vect3f& pos) {
    mEngine->getResourceManager()->getResource<Music>(*mCurrentMusic)->setPosition(pos);
}

void MusicQueue::setVolume(const float& volume) {
    mEngine->getResourceManager()->getResource<Music>(*mCurrentMusic)->setVolume(volume);
}

void MusicQueue::setPitch(const float& pitch) {
    mEngine->getResourceManager()->getResource<Music>(*mCurrentMusic)->setPitch(pitch);
}

AudioStatus MusicQueue::getStatus() {
    return mStatus;
}

unsigned int MusicQueue::getPlayingOffSet() {
    return mEngine->getResourceManager()->getResource<Music>(*mCurrentMusic)->getPlayingOffSet();
}

void MusicQueue::setPlayingOffSet(const unsigned int offSet) {
    mEngine->getResourceManager()->getResource<Music>(*mCurrentMusic)->setPlayingOffSet(offSet);
}


// We set to play the queue in a random order
// Which don't make much sense since its a QUEUE
// But anyways, its interessant to implement this function
// To our in game music
void MusicQueue::setRandomPlay(const bool& random) {
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

void MusicQueue::setLoopMode(const bool& loop) {
    mIsLoopMode = loop;
}

void MusicQueue::play() {
    mStatus = AudioStatus::PLAYING;
    mEngine->getResourceManager()->getResource<Music>(*mCurrentMusic)->play();
}

void MusicQueue::pause() {
    mStatus = AudioStatus::PAUSED;
    mEngine->getResourceManager()->getResource<Music>(*mCurrentMusic)->pause();
}

void MusicQueue::stop() {
    mStatus = AudioStatus::STOPPED;
    mEngine->getResourceManager()->getResource<Music>(*mCurrentMusic)->stop();
}

void MusicQueue::update() {
    if (mCurrentMusic != mMusics.end()) {
        AudioStatus status = mEngine->getResourceManager()->getResource<Music>(*mCurrentMusic)->getStatus();   

        if (status == AudioStatus::STOPPED) {
            mStatus = AudioStatus::STOPPED;
            mCurrentMusic++;

            if (mCurrentMusic == mMusics.end()) {
                if (isRandomPlay()) {
                    mMusics.sort();
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

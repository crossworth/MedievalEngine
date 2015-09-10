#ifndef MUSICQUEUE_H
#define MUSICQUEUE_H
#include <list>
#include "Resources/ResourceIDGenerator.h"
#include "Resources/Music.h"

namespace ME  {

class MedievalEngine;

class MusicQueue : public Resource, public Audible {
public:
    MusicQueue();

    void registerEngine(MedievalEngine* engine);

    void insert(ResourceID& music);
    void insert(const std::string& music);

    unsigned int getDuration();
    float getAttenuation();
    float getMinDistance();
    bool isRelativeToListener();
    Vect3f getPosition();
    float getVolume();
    float getPitch();
    void setAttenuation(const float& attenuation);
    void setMinDistance(const float& distance);
    void setRelativeToListener(const bool& relative);
    void setPosition(const Vect3f& pos);
    void setVolume(const float& volume);
    void setPitch(const float& pitch);
    Audio::AudioStatus getStatus();
    unsigned int getPlayingOffSet();
    void setPlayingOffSet(const unsigned int offset);

    // We set to play the queue in a random order
    // Which don't make much sense since its a QUEUE
    // But anyways, its interessant to implement this function
    // To our in game music
    void setRandomPlay(const bool& random);
    bool isRandomPlay();

    // Here the loop mode works a litte bit different
    // We gonna loop all the queue and not only one music
    bool isLoopMode();
    void setLoopMode(const bool& loop);
    void play();
    void pause();
    void stop();

    void update();
private:
    bool mIsLoopMode;
    bool mIsRandomPlay;
    MedievalEngine* mEngine;
    std::list<ResourceID> mMusics;
    std::list<ResourceID>::iterator mCurrentMusic;
    Audio::AudioStatus mStatus;
};

}


#endif // MUSICQUEUE_H

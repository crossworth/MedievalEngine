#ifndef MEDIEVALENGINE_RESOURCES_MUSICQUEUE_H_
#define MEDIEVALENGINE_RESOURCES_MUSICQUEUE_H_
#include <algorithm>

#include "Resources/Music.h"

namespace ME  {

class MusicQueue : public Resource, public Audible {
public:
    MusicQueue();

    void updateVolume();

    void insert(const std::string &music);

    uint32 getDuration();
    float getAttenuation();
    float getMinDistance();
    bool isRelativeToListener();
    Vect3f getPosition();
    float getVolume();
    float getPitch();
    void setAttenuation(const float &attenuation);
    void setMinDistance(const float &distance);
    void setRelativeToListener(const bool &relative);
    void setPosition(const Vect3f &pos);
    void setVolume(const float &volume);
    void setPitch(const float &pitch);
    Audible::AudioStatus getStatus();
    uint32 getPlayingOffSet();
    void setPlayingOffSet(const uint32 &offset);

    // We set to play the queue in a random order
    // Which don't make much sense since its a QUEUE
    // But anyways, its interessant to implement this function
    // To our in game music
    void setRandomPlay(const bool &random);
    bool isRandomPlay();

    // Here the loop mode works a litte bit different
    // We gonna loop all the queue and not only one music
    bool isLoopMode();
    void setLoopMode(const bool &loop);
    void play();
    void pause();
    void stop();

    void update();
private:
    bool mIsLoopMode;
    bool mIsRandomPlay;

    std::vector<std::string> mMusics;
    std::vector<std::string>::iterator mCurrentMusic;

    Audible::AudioStatus mStatus;
};

}


#endif // MEDIEVALENGINE_RESOURCES_MUSICQUEUE_H_

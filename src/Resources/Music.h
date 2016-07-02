#ifndef MUSIC_H
#define MUSIC_H
#include "LogInc.h"

#include "Audio/Audible.h"

#include "Resources/Resource.h"

namespace ME{

class Music : public Resource, public Audible {
public:
    Music();
    bool loadFromFile(const std::string &fileName, const Audible::AudioType &type = Audible::AudioType::MUSIC);
    sf::Music* getResourcePointer();

    void updateVolume();

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
    bool isLoopMode();
    void setLoopMode(const bool &loop);
    void play();
    void pause();
    void stop();
private:
    sf::Music mMusic;
};

}

#endif // MUSIC_H

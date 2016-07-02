#ifndef MEDIEVALENGINE_RESOURCES_SOUND_H_
#define MEDIEVALENGINE_RESOURCES_SOUND_H_
#include "LogInc.h"
#include "Resources/Resource.h"
#include "Audio/Audible.h"


namespace ME{

class Sound : public Resource, public Audible {
public:
    // TODO(Pedro): Remove the constructor that can fail
    Sound(const std::string& fileName, const Audible::AudioType& type = Audible::AudioType::MUSIC);
    sf::Sound* loadFromFile(const std::string& fileName, const Audible::AudioType& type = Audible::AudioType::MUSIC);
    sf::Sound* getResourcePointer();

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
    sf::Sound mSound;
    sf::SoundBuffer mSoundBuffer;
};

}

#endif // MEDIEVALENGINE_RESOURCES_SOUND_H_

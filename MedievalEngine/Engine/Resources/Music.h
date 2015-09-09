#ifndef MUSIC_H
#define MUSIC_H
#include "LogInc.h"
#include "Resources/Resource.h"
#include "Audio/Audible.h"

namespace ME{

class Music : public Resource, public Audible {
public:
    Music(const std::string& fileName, const Audio::AudioType& type = Audio::AudioType::MUSIC);
    sf::Music* loadFromFile(const std::string& fileName, const Audio::AudioType& type = Audio::AudioType::MUSIC);
    sf::Music* getResourcePointer();

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
    bool isLoopMode();
    void setLoopMode(const bool& loop);
    void play();
    void pause();
    void stop();
private:
    sf::Music mMusic;
};

}

#endif // MUSIC_H

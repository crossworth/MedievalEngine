#ifndef SOUND_H
#define SOUND_H
#include <LogInc.h>
#include <Assets/Asset.h>
#include <Audio/Audible.h>


namespace ME{

class Sound : public Asset, public Audible {
public:
    Sound(const std::string& fileName);
    sf::Sound* loadFromFile(const std::string& fileName);
    sf::Sound* getResourcePointer();

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
    AUDIABLE_STATUS getStatus();
    unsigned int getPlayingOffSet();
    void setPlayingOffSet(const unsigned int offSet);
    bool isLoopMode();
    void setLoopMode(const bool& loop);
    void play();
    void pause();
    void stop();
private:
    sf::Sound mSound;
    sf::SoundBuffer mSoundBuffer;
};

}

#endif // SOUND_H

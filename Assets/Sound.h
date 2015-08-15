#ifndef SOUND_H
#define SOUND_H
#include <Assets/Asset.h>
#include <Audio/Audible.h>
#include <LogInc.h>

namespace ME{

class Sound : public Asset, public Audible {
public:
    Sound(const std::string &fileName);
    sf::Sound* loadFromFile(const std::string &fileName);
    sf::Sound* getResourcePointer();

    sf::Time getDuration();
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
    AUDIABLE_STATUS getStatus();
    sf::Time getPlayingOffSet();
    void setPlayingOffSet(const sf::Time &offSet);
    bool isLoopMode();
    void setLoopMode(const bool &loop);
    void play();
    void pause();
    void stop();

private:
    sf::Sound mSound;
    sf::SoundBuffer mBuffer;
};

}

#endif // SOUND_H
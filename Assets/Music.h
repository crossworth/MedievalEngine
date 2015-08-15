#ifndef MUSIC_H
#define MUSIC_H
#include <Assets/Asset.h>
#include <Audio/Audible.h>
#include <LogInc.h>

namespace ME{

class Music : public Asset, public Audible {
public:
    Music(const std::string &fileName);
    sf::Music* loadFromFile(const std::string &fileName);
    sf::Music* getResourcePointer();

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
    sf::Music mMusic;
};

}

#endif // MUSIC_H

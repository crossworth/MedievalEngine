#ifndef AUDIBLE_H
#define AUDIBLE_H
#include <SFML/Audio.hpp>
#include <Helper/Vect3.h>


namespace ME{

enum AUDIABLE_STATUS {STOPPED, PLAYING, PAUSED};

class Audible {
public:
    Audible();
    virtual unsigned int getDuration() = 0;
    virtual float getAttenuation() = 0;
    virtual float getMinDistance() = 0;
    virtual bool isRelativeToListener() = 0;
    virtual Vect3f getPosition() = 0;
    virtual float getVolume() = 0;
    virtual float getPitch() = 0;
    virtual void setAttenuation(const float& attenuation) = 0;
    virtual void setMinDistance(const float& distance) = 0;
    virtual void setRelativeToListener(const bool& relative) = 0;
    virtual void setPosition(const Vect3f& pos) = 0;
    virtual void setVolume(const float& volume) = 0;
    virtual void setPitch(const float& pitch) = 0;
    virtual AUDIABLE_STATUS getStatus() = 0;
    virtual unsigned int getPlayingOffSet() = 0;
    virtual void setPlayingOffSet(const unsigned int offSet) = 0;
    virtual bool isLoopMode() = 0;
    virtual void setLoopMode(const bool& loop) = 0;
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
};

}

#endif // AUDIBLE_H

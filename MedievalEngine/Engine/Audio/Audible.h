#ifndef AUDIBLE_H
#define AUDIBLE_H
#include <SFML/Audio.hpp>
#include "Config.h"
#include "Helper/Vect3.h"


namespace ME{


// TODO(Pedro): Put this enum's on a namespace

/**
 * AudioStatus
 * The current Audio Status
 */
enum AudioStatus {
    STOPPED, ///< Audio is stopped
    PLAYING, ///< Audio is playing
    PAUSED   ///< Audio is paused
};

/**
 * AudioType enum
 * The type of the sound/music
 */
enum AudioType {
    MUSIC,  ///< Type music
    VOICE,  ///< Type voice
    AMBIENT ///< Type ambient
};

/**
 * @brief The Audible class
 * Define the base class of sound and music
 */
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
    virtual AudioStatus getStatus() = 0;
    virtual unsigned int getPlayingOffSet() = 0;
    virtual void setPlayingOffSet(const unsigned int offset) = 0;
    virtual bool isLoopMode() = 0;
    virtual void setLoopMode(const bool& loop) = 0;
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;

    AudioType getType();
    void setType(const AudioType& type);
public:
    // TODO(Pedro): rename this VOLUME -> GLOBAL_VOLUME
    static float VOLUME;
    static float VOICE_VOLUME;
    static float MUSIC_VOLUME;
    static float AMBIENT_VOLUME;
protected:
    AudioType mAudioType;
};

}

#endif // AUDIBLE_H

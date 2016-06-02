#ifndef MEDIEVALENGONE_AUDIO_AUDIBLE_H_
#define MEDIEVALENGONE_AUDIO_AUDIBLE_H_

#include <SFML/Audio.hpp>

#include "Config.h"
#include "Helper/Vect3.h"
#include "Lua/LuaAPI.h"

namespace ME{

/**
 * @namespace ME::Audio
 * @brief The Audio namespace with all the enum's for the audio related functions
 *
 */
namespace Audio {
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

}

/**
 * The Audible class
 * Define the base class of sound and music
 */
class Audible {
public:

    /**
     * The default empty constructor
     */
    Audible();

    virtual void updateVolume() = 0;

    /**
     * Return the duration of the sound/music
     * @return  unsigned int - duration in milliseconds
     */
    virtual unsigned int getDuration() = 0;

    /**
     * Get the sound/music attenuation factor
     * @return float - attenuation
     */
    virtual float getAttenuation() = 0;

    /**
     * Get the minimum distance of a sound/music<br>
     *
     * @see ME::Audble::getMinDistance
     *
     * @return float - minimum distance
     */
    virtual float getMinDistance() = 0;

    /**
     * If the sound/music is relative to the Listerner<br>
     *
     * @see ME::Audbible::setRelativeToListener
     *
     * @return bool - is relative or absolute
     */
    virtual bool isRelativeToListener() = 0;

    /**
     * Get the 3D position of the sound in the audio scene.
     * @return ME::Vect3f - 3d position
     */
    virtual Vect3f getPosition() = 0;

    /**
     * Get the volume of the sound/music<br>
     * NOTE(Pedro): We calculate the volume based on the ME::Audio::GLOBAL_VOLUME<br>
     * and the volume type of the sound/music
     * @return float - volume
     */
    virtual float getVolume() = 0;

    /**
     * Get the pitch of the music/sound
     * @return float - pitch of the music/sound
     */
    virtual float getPitch() = 0;

    /**
     *
     * The attenuation is a multiplicative factor which makes the sound/music more<br>
     * or less loud according to its distance from the listener. An attenuation<br>
     * of 0 will produce a non-attenuated sound, i.e. its volume will always be<br>
     * the same whether it is heard from near or from far. On the other hand, an<br>
     * attenuation value such as 100 will make the sound fade out very quickly as<br>
     * it gets further from the listener. The default value of the attenuation is 1.<br>
     *
     * @see ME::Audbile::getAttenuation
     *
     * @param float - attenuation
     */
    virtual void setAttenuation(const float& attenuation) = 0;

    /**
     * The "minimum distance" of a sound/music is the maximum distance at which<br>
     * it is heard at its maximum volume. Further than the minimum distance,<br>
     * it will start to fade out according to its attenuation factor.<br>
     * A value of 0 ("inside the head of the listener") is an invalid value<br>
     * and is forbidden. The default value of the minimum distance is 1.<br>
     *
     * @see ME::Audble::getMinDistance
     *
     * @param float - distance
     */
    virtual void setMinDistance(const float& distance) = 0;

    /**
     * [setRelativeToListener description]
     * @param relative [description]
     */
    virtual void setRelativeToListener(const bool& relative) = 0;
    virtual void setPosition(const Vect3f& pos) = 0;
    virtual void setVolume(const float& volume) = 0;
    virtual void setPitch(const float& pitch) = 0;
    virtual Audio::AudioStatus getStatus() = 0;
    virtual unsigned int getPlayingOffSet() = 0;
    virtual void setPlayingOffSet(const unsigned int offset) = 0;

    /**
     * If we are looping or not the sound/music
     * @return bool - if we are looping the sound/music
     */
    virtual bool isLoopMode() = 0;

    /**
     * Set whether the sound/music should loop or not
     * @param bool - if we should loop
     */
    virtual void setLoopMode(const bool& loop) = 0;

    /**
     * Play the current sound/music
     */
    virtual void play() = 0;

    /**
     * Pause the current sound/music
     */
    virtual void pause() = 0;

    /**
     * Stop the current sound/music
     */
    virtual void stop() = 0;

    /**
     * Get the type of sound/music
     * @return ME::Audio::AudioType - the type of audio
     */
    Audio::AudioType getType();

    /**
     * Set the type of sound/music
     * @param ME::Audio::AudioType - the type of audio
     */
    void setType(const Audio::AudioType& type);
public:
    /**
     * The Global Volume of engine (volume master or volume base)
     */
    static float GLOBAL_VOLUME;

    /**
     * The Voice Volume of engine
     */
    static float VOICE_VOLUME;

    /**
     * The Music Volume of engine
     */
    static float MUSIC_VOLUME;

    /**
     * The Ambient Volume of the engine
     */
    static float AMBIENT_VOLUME;

protected:
    Audio::AudioType mAudioType;
    static bool mIsFunctionsExported;
    void exportFunctions();
};

}

#endif // MEDIEVALENGONE_AUDIO_AUDIBLE_H_

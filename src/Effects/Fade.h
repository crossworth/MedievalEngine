#ifndef FADE_H
#define FADE_H
#include "Effects/Effect.h"


namespace ME {

/**
 * The Fade Class
 */
class Fade : public Effect {
public:
    /**
     * The Fade type
     */
    enum Type {
        FADEIN, ///< Fade in
        FADEOUT ///< Fade out
    };
public:

    /**
     * Fade constructor
     * @param double time - Time in milliseconds that determine how long the effect will take
     * @param Fade::Type& type - The type of Fade effect
     * @param VoidCallback func - Callback function to be called once the effect its done
     */
    Fade(double time, const Type& type, VoidCallback func = EMPTY_VOID_CALLBACK);

    /**
     * Update the fade effect
     * @param  Drawable* object - The object to apply the effect
     * @return  sf::RenderStates* - Return an updated state with all the changes
     */
    void update(Drawable* object);
private:
	Fade();
    double mFadeTime;
    Type mFadeType;
    double mFadeCounter;
};

}

#endif // FADE_H

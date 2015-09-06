#ifndef FADE_H
#define FADE_H
#include "Effects/Effect.h"


namespace ME {

class Fade : public Effect {
public:
    enum Type {FADEIN, FADEOUT};
public:
    // Em milesegundos
    Fade(double time, const Type& type, VoidCallback func = EMPTY_VOID_CALLBACK);
    sf::RenderStates* update(Drawable* object);
private:
	Fade();
    double mFadeTime;
    Type mFadeType;
    double mFadeCounter;
};

}

#endif // FADE_H

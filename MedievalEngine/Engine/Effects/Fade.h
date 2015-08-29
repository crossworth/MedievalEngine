#ifndef FADE_H
#define FADE_H
#include "Effects/Effect.h"


namespace ME {

class Fade : public Effect {
public:
    enum Type {FADEIN, FADEOUT};
public:
    // Em milesegundos
    Fade(double time, const Type& type, Effect::Callback func = EMPTY_FUNCTION);
    void update(Drawable* object);
private:
	Fade();
    double mFadeTime;
    Type mFadeType;
    double mFadeCounter;
};

}

#endif // FADE_H

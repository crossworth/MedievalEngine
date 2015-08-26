#ifndef FADE_H
#define FADE_H
#include "Effects/Effect.h"


namespace ME {

class Fade : public Effect {
public:
    enum Type {FADEIN, FADEOUT};
public:
    Fade(int time, const Type& type);
    void update(Drawable* object);
private:
	Fade();
    unsigned int mFadeTime;
    Type mFadeType;
    float mFadeCounter;
};

}

#endif // FADE_H

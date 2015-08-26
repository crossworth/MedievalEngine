#ifndef EFFECT_H
#define EFFECT_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Helper/Clock.h"
#include "Graphics/Drawable.h"


namespace ME {

class Drawable;

class Effect {
public:
    enum Type { FADE, STROBE, BLUR, BLOM };
public:
    Effect();
    virtual void update(Drawable* object) = 0;
    Type getType();
    std::string getTypeStd();

    void resetClock();
    void setDone();
    bool isDone();
protected:
    Type mType;
    Clock mClock;
    bool mDone;
};


}
#endif // EFFECT_H
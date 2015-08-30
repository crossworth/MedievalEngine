#ifndef EFFECT_H
#define EFFECT_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Helper/Types.h"
#include "Helper/Clock.h"
#include "Graphics/Drawable.h"


namespace ME {

class Drawable;

class Effect {
public:
    enum Type {FADE, STROBE, SHADER};
public:
    Effect();
    virtual void update(Drawable* object) = 0;
    Type getType();
    std::string getTypeStd();

    void restartClock();
    void setDone();
    bool isDone();
    void registerRenderStates(sf::RenderStates* states);
protected:
    sf::RenderStates* mRenderStates;
    VoidCallback mCallback;
    Type mType;
    Clock mClock;
    bool mDone;
};


}
#endif // EFFECT_H

#ifndef EFFECT_H
#define EFFECT_H
#include <iostream>
#include <memory>
#include <functional>
#include <SFML/Graphics.hpp>
#include "Helper/Clock.h"
#include "Graphics/Drawable.h"

#define EMPTY_FUNCTION [](void) {}

namespace ME {

class Drawable;

class Effect {
public:
    typedef std::function<void(void)> Callback;
    enum Type { FADE, STROBE, BLUR, BLOM };
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
    Callback mCallback;
    Type mType;
    Clock mClock;
    bool mDone;
};


}
#endif // EFFECT_H

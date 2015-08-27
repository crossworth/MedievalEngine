#ifndef STROBE_H
#define STROBE_H
#include "Effects/Effect.h"


namespace ME {

class Strobe : public Effect {
public:
    // A forma que funciona é bem simples
    // irá criar um efeito com base no negative range
    // Por exemplo, um negative range de 0.5 irá criar
    // um efeito da opacidade default do objeto até 50% abaixo
    // Ou seja um objeto com 1.0f de opacidade teria um
    // strobe de até 50% de opacidade

    Strobe(unsigned int time, float negativeRange, unsigned int duration = 50000, Effect::Callback func = EMPTY_FUNCTION);
    void update(Drawable* object);
private:
    bool mIsInitialized;
    int mDirection;
    Color mBaseColor;
    unsigned int mStrobeTime;
    float mStrobeCounter;
    float mNegativeRange;
    unsigned int mDuration;
    Clock mClockDuration;
};

}

#endif // STROBE_H

#ifndef STROBE_H
#define STROBE_H
#include "Effects/Effect.h"


namespace ME {

class Strobe : public Effect {
public:
    // A forma que funciona � bem simples
    // Ir� criar um efeito com base no negative range
    // Por exemplo, um negative range de 0.5 ir� criar
    // um efeito da opacidade default do objeto at� 50% abaixo
    // Ou seja um objeto com 1.0f de opacidade teria um
    // strobe de at� 50% de opacidade

    Strobe(double time, float negativeRange, unsigned int duration = 50000, VoidCallback func = EMPTY_VOID_CALLBACK);
    sf::RenderStates* update(Drawable* object);
private:
    bool mIsInitialized;
    int mDirection;
    Color mBaseColor;
    double mStrobeTime;
    double mStrobeCounter;
    float mNegativeRange;
    double mDuration;
    Clock mClockDuration;
};

}

#endif // STROBE_H

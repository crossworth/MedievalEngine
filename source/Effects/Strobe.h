#ifndef STROBE_H
#define STROBE_H
#include "Effects/Effect.h"


namespace ME {

class Strobe : public Effect {
public:
    /**
     * Create a Strobe effect<br>
     * The way this work's is quite simple<br>
     * We provide the base nagative range for the fade effect<br>
     * Exemple: A negative range of 0.5f will create a effect<br>
     * of fade from the object opacity until the 50% lower the object opacity.<br>
     * That's means that one object with a opacity of 1.0f with a negative range will<br>
     * go from 1.0f opacity until 0.5f and than goes back to 1.0f<br>
     * 
     * NOTE(Pedro): If only one reference is applied to multiple object's all the objects<br>
     * will have the effect synchronized with the first object<br>
     * to have independent strobe effect's you must create multiples strobe object's 
     * 
     * @param unsigned int - time in milliseconds to the strobe effect update the transitions
     * @param float - negative range of the strobe value from 0.0f to 1.0f
     * @param unsigned int - duration in milliseconds to the strobe effect be considered done, -1 to infinity
     * @param ME::VoidCallback - a function to be called once the effect it's considered done
     */
    Strobe(unsigned int time, float negativeRange, unsigned int duration = 50000, VoidCallback func = EMPTY_VOID_CALLBACK);
    void update(Drawable* object);
private:
    bool mIsInitialized;
    float mDirection;
    Color mBaseColor;
    float mStrobeTime;
    double mStrobeCounter;
    float mNegativeRange;
    unsigned int mDuration;
    Clock mClockDuration;
};

}

#endif // STROBE_H

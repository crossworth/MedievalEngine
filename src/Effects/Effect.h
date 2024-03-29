#ifndef EFFECT_H
#define EFFECT_H
#include "Helper/Clock.h"
#include "Graphics/Drawable.h"


namespace ME {

class Drawable;

class Effect {
public:
    /**
     * Effect Type
     * Define the type of effect
     */
    enum Type {
        FADE,   ///< Fade type
        STROBE, ///< Strobe type
        SHADER  ///< Shade type
    };
public:
    Effect();
    virtual void update(Drawable* object) = 0;
    Type getType();

    std::string getTypeStr();

    void restartClock();
    void setDone();
    bool isDone();
protected:
    VoidCallback mCallback;
    Type mType;
    Clock mClock;
    bool mDone;
};


}
#endif // EFFECT_H

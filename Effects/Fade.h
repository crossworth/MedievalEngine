#ifndef FADE_H
#define FADE_H
#include <Effects/Effects.h>


namespace ME {

enum FADE_TYPE {FADEIN, FADEOUT};

class Fade : public Effects {
public:
    // TODO: normalize time
    Fade(float time, const FADE_TYPE& type);
    void update(Drawable* object);
    bool done();

private:
    float mFadeTime;
    FADE_TYPE mFadeType;
    float mFadeCounter;
};

}

#endif // FADE_H

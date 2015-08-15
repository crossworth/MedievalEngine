#ifndef FADE_H
#define FADE_H
#include <Effects/Effects.h>

namespace ME {

enum FADE_TYPE {FADEIN, FADEOUT};

class Fade : public Effects {
public:
    Fade(float time, const FADE_TYPE &type);
    void update(Drawable *object);
    bool done();

private:
    float mTimeAn;
    FADE_TYPE _mTypeFade;
    float mFadeCounter;
};

}

#endif // FADE_H

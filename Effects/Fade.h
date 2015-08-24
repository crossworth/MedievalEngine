#ifndef FADE_H
#define FADE_H
#include <Effects/Effects.h>


namespace ME {



class Fade : public Effects {
public:
    enum FADE_TYPE {FADEIN, FADEOUT};
public:
    Fade(unsigned int time, const FADE_TYPE& type);
    void update(Drawable* object);
    bool done();

private:
    unsigned int mFadeTime;
    FADE_TYPE mFadeType;
    float mFadeCounter;
};

}

#endif // FADE_H

#ifndef FADE_H
#define FADE_H
#include <Effects/Effects.h>


namespace ME {

class Fade : public Effects {
public:
    enum FadeType {FADEIN, FADEOUT};
public:
    Fade(unsigned int time, const FadeType& type);
    void update(Drawable* object);
    bool done();

private:
    unsigned int mFadeTime;
    FadeType m_fadeType;
    float mFadeCounter;
};

}

#endif // FADE_H

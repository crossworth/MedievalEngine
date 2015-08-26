#ifndef FADE_H
#define FADE_H
#include <Effects/Effects.h>


namespace ME {

class Fade : public Effects {
public:
    enum Type {FADEIN, FADEOUT};
public:
    Fade(unsigned int time, const Type& type);
    void update(Drawable* object);
    bool done();

private:
    unsigned int mFadeTime;
    Type m_fadeType;
    float mFadeCounter;
};

}

#endif // FADE_H

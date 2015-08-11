#ifndef FADE_H
#define FADE_H
#include "effects.h"

namespace ME {

class Fade : public Effects {
public:
    Fade(Sprite *sprite, const FADE_TYPE &type, float timeSeconds, const std::string &spriteName);
    void draw();
    void update();
    bool done();

    ~Fade();
private:
    float mTimeAn;
    Sprite *mSprite;
    FADE_TYPE mType;
    int mFadeCounter;
    float mStep;
};

}

#endif // FADE_H

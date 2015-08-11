#include "fade.h"

using namespace ME;

Fade::Fade(Sprite *sprite, const FADE_TYPE &type, float timeSeconds, const std::string &spriteName) {
    // Time em milisegundos
    mTimeAn = timeSeconds;
    mSprite = sprite;
    mType   = type;

    mSpriteName = spriteName;

    mDone = false;

    if (mType == FADEOUT) {
        mFadeCounter = 255;
        mEffectName = "fadeOut";
    } else {
        mEffectName = "fadeIn";
        mFadeCounter = 0;
    }

    mStep = mTimeAn/255;
}


bool Fade::done() {
    return mDone;
}

void Fade::draw() {
    mSprite->setColor(sf::Color(255, 255, 255, mFadeCounter));
}

Fade::~Fade() {

}

void Fade::update() {
    sf::Time mTime = mClock.getElapsedTime();

    // O código abaixo utiliza de mágia para funcionar
    // + de 1 hora para fazer ele funcionar
    // Tentativa e erro foram aplicados

    if (mTime.asSeconds() >= mStep) {
        if (mType == FADEOUT) {
            mFadeCounter = mFadeCounter - (255/(mTime.asSeconds()*1000));

            if (mFadeCounter <= 0) {
                mFadeCounter = 0;
                mDone = true;
            }
        } else {
            mFadeCounter = mFadeCounter + (255/(mTime.asSeconds()*1000));

            if (mFadeCounter >= 255) {
                mFadeCounter = 255;
                mDone = true;
            }
        }
        mClock.restart();
    }
}

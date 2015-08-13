#include "Fade.h"

using namespace ME;

Fade::Fade(Sprite *sprite, const FADE_TYPE &type, float timeSeconds, const std::string &spriteName) {
    // Time em milisegundos
    mTimeAn     = timeSeconds;
    mSprite     = sprite;
    mType       = type;
    mSpriteName = spriteName;

    mDone = false;

    if (mType == FADEOUT) {
        mFadeCounter = 255.0f;
        mEffectName = "fadeOut";
    } else {
        mEffectName = "fadeIn";
        mFadeCounter = 0.0f;
    }
}

bool Fade::done() {
    return mDone;
}

void Fade::draw() {
    sf::Color tmpColor = mSprite->getColor();
    mSprite->setColor(sf::Color(tmpColor.r, tmpColor.g, tmpColor.b, static_cast<int>(mFadeCounter)));
}

Fade::~Fade() {

}

void Fade::update() {
    sf::Time mTime = mClock.getElapsedTime();

    // O código abaixo utiliza de mágia para funcionar
    // + de 3 hora para fazer ele funcionar
    // Tentativa e erro foram aplicados

    // Basicamente, ele faz contas para calcular a opacidade de um elemento
    // de acordo com um tempo passado como argumento.

    // Utiliza float para os cálculos, porém clipa na hora de exibir em int
    // Precisão de 2 casas, not bad =)

    float mStep =  (mTime.asSeconds() * 255)/mTimeAn;

    if (mType == FADEOUT) {
        mFadeCounter = mFadeCounter - mStep;

        if (mFadeCounter <= 0.0f) {
            mFadeCounter = 0.0f;
            mDone = true;
        }
    } else {
        mFadeCounter = mFadeCounter + mStep;

        if (mFadeCounter >= 255.0f) {
            mFadeCounter = 255.0f;
            mDone = true;
        }
    }
    mClock.restart();
}

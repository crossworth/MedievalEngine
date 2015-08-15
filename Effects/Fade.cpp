#include "Fade.h"

using namespace ME;

Fade::Fade(float time, const FADE_TYPE &type) {
    mType = "fade";

    // Time em milisegundos
    mTimeAn     = time;
    _mTypeFade  = type;

    if (_mTypeFade == FADEOUT) {
        mFadeCounter = 255.0f;
        mType        = "fadeOut";
    } else {
        mType        = "fadeIn";
        mFadeCounter = 0.0f;
    }
}

bool Fade::done() {
    return mDone;
}

void Fade::update(Drawable *object) {
    if (!done()) {
        sf::Time mTime = mClock.getElapsedTime();

        // O código abaixo utiliza de mágia para funcionar
        // + de 3 hora para fazer ele funcionar
        // Tentativa e erro foram aplicados

        // Basicamente, ele faz contas para calcular a opacidade de um elemento
        // de acordo com um tempo passado como argumento.

        // Utiliza float para os cálculos, porém clipa na hora de exibir em int
        // Precisão de 2 casas, not bad =)

        float mStep =  (mTime.asSeconds() * 255)/mTimeAn;

        if (_mTypeFade == FADEOUT) {
            mFadeCounter = mFadeCounter - mStep;

            if (mFadeCounter <= 0.0f) {
                mFadeCounter = 0.0f;
                mDone = true;
                LOG << Log::VERBOSE << ("[Fade::update] Effect " +  getType() + " done").c_str() << std::endl;
            }
        } else {
            mFadeCounter = mFadeCounter + mStep;

            if (mFadeCounter >= 255.0f) {
                mFadeCounter = 255.0f;
                mDone = true;
                LOG << Log::VERBOSE << ("[Fade::update] Effect " +  getType() + " done").c_str() << std::endl;
            }
        }
        mClock.restart();

        Color tmpColor = object->getColor();
        object->setColor(Color(tmpColor.red, tmpColor.green, tmpColor.blue, static_cast<int>(mFadeCounter)));
    }
}

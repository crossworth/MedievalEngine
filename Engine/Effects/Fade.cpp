#include "Fade.h"

using namespace ME;

Fade::Fade(int time, const Type &type) {
    mType = Effect::Type::FADE;

    // Tempo em milisegundos
    mFadeTime = time;
    mFadeType = type;

    if (mFadeType == Type::FADEOUT) {
        mFadeCounter = 255.0f;
        mFadeType   = Type::FADEOUT;
    } else {
        mFadeType   = Type::FADEIN;
        mFadeCounter = 0.0f;
    }
}

void Fade::update(Drawable* object) {
    if (!isDone()) {
        // O código abaixo utiliza de mágia para funcionar
        // + de 1 hora para fazer ele funcionar
        // Tentativa e erro foram aplicados

        // Basicamente, ele faz contas para calcular a opacidade de um elemento
        // de acordo com um tempo passado como argumento.

        // Utiliza float para os cálculos, porém clipa na hora de exibir em int
        // Precisão de 2 casas, not bad =)


        float mStep =  (mClock.getTime() * 255) / mFadeTime;

        if (mFadeType == Type::FADEOUT) {
            mFadeCounter = mFadeCounter - mStep;

            if (mFadeCounter <= 0.0f) {
                mFadeCounter = 0.0f;
                mDone = true;
                LOG << Log::VERBOSE << Log::getTime()
                    << ("[Fade::update] Effect " +
                                        getTypeStd() + " done").c_str() << std::endl;
            }
        } else {
            mFadeCounter = mFadeCounter + mStep;

            if (mFadeCounter >= 255.0f) {
                mFadeCounter = 255.0f;
                mDone = true;
                LOG << Log::VERBOSE << Log::getTime()
                << ("[Fade::update] Effect " +
                                        getTypeStd() + " done").c_str() << std::endl;
            }
        }
        restartClock();

        Color tmpColor = object->getColor();
        object->setColor(Color(tmpColor.red, tmpColor.green,
                               tmpColor.blue, static_cast<int>(mFadeCounter)));
    }
}

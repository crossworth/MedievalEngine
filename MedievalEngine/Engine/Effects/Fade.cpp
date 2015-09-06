#include "Fade.h"

using namespace ME;

Fade::Fade(double time, const Type &type, VoidCallback func) {
    mType     = Effect::Type::FADE;
    mCallback = VoidCallback(func);

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

sf::RenderStates* Fade::update(Drawable* object) {
    if (!isDone()) {
        // UTF-8 que removeu todos os acentos =/
        // O codigo abaixo utiliza de magia para funcionar
        // + de 1 hora para fazer ele funcionar
        // Tentativa e erro foram aplicados

        // Basicamente, ele faz contas para calcular a opacidade de um elemento
        // de acordo com um tempo passado como argumento.

        // Utiliza float para os calculos, porem clipa na hora de exibir em int
        // Precisao de 2 casas, not bad =)

        double mStep =  (mClock.getTime() * 255) / mFadeTime;

        if (mFadeType == Type::FADEOUT) {
            mFadeCounter = mFadeCounter - mStep;

            if (mFadeCounter <= 0.0f) {
                mFadeCounter = 0.0f;
                setDone();
            }
        } else {
            mFadeCounter = mFadeCounter + mStep;
            if (mFadeCounter >= 255.0f) {
                mFadeCounter = 255.0f;
                setDone();
            }
        }
        restartClock();

        Color tmpColor = object->getColor();
        object->setColor(Color(tmpColor.red, tmpColor.green,
                               tmpColor.blue, static_cast<int>(mFadeCounter)));
    }

    return new sf::RenderStates();
}

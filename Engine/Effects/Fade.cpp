#include "Fade.h"

using namespace ME;

Fade::Fade(unsigned int time, const FadeType &type) {
    m_type = EffectType::FADE;

    // Tempo em milisegundos
    mFadeTime  = time;
    m_fadeType = type;

    if (m_fadeType == FadeType::FADEOUT) {
        mFadeCounter = 255.0f;
        m_fadeType   = FadeType::FADEOUT;
    } else {
        m_fadeType   = FadeType::FADEOUT;
        mFadeCounter = 0.0f;
    }
}

bool Fade::done() {
    return m_done;
}

void Fade::update(Drawable* object) {
    if (!done()) {
        sf::Time mTime = mClock.getElapsedTime();

        // O código abaixo utiliza de mágia para funcionar
        // + de 3 hora para fazer ele funcionar
        // Tentativa e erro foram aplicados

        // Basicamente, ele faz contas para calcular a opacidade de um elemento
        // de acordo com um tempo passado como argumento.

        // Utiliza float para os cálculos, porém clipa na hora de exibir em int
        // Precisão de 2 casas, not bad =)

        float mStep =  (mTime.asMilliseconds() * 255)/mFadeTime;

        if (m_fadeType == FADEOUT) {
            mFadeCounter = mFadeCounter - mStep;

            if (mFadeCounter <= 0.0f) {
                mFadeCounter = 0.0f;
                m_done = true;
                LOG << Log::VERBOSE << ("[Fade::update] Effect " +
                                        getTypeStd() + " done").c_str() << std::endl;
            }
        } else {
            mFadeCounter = mFadeCounter + mStep;

            if (mFadeCounter >= 255.0f) {
                mFadeCounter = 255.0f;
                m_done = true;
                LOG << Log::VERBOSE << ("[Fade::update] Effect " +
                                        getTypeStd() + " done").c_str() << std::endl;
            }
        }
        mClock.restart();

        Color tmpColor = object->getColor();
        object->setColor(Color(tmpColor.red, tmpColor.green,
                               tmpColor.blue, static_cast<int>(mFadeCounter)));
    }
}

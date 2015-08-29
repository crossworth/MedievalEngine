#ifndef BLUR_H
#define BLUR_H
#include "Effects/Effect.h"

namespace ME {

class Blur : public Effect {
public:
    Blur(const float& amount = 0.0f);
    void setAmount(const float& amount);
    void update(Drawable *object);
private:
    bool isShaderEnable();

    Blur();
    float mAmount;
    sf::Shader mShader;
    bool mIsShaderEnable;
};

}

#endif // BLUR_H

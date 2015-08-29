#ifndef BLUR_H
#define BLUR_H
#include "Effects/Effect.h"

namespace ME {

class Blur : public Effect {
public:
    Blur(const double& amount = 0.0f);
    void setAmount(const double& amount);
    void update(Drawable *object);
private:
    bool isShaderEnable();

    Blur();
    double mAmount;
    sf::Shader mShader;
    bool mIsShaderEnable;
};

}

#endif // BLUR_H

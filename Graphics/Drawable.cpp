#include "Drawable.h"
#include <Effects/Effects.h>

using namespace ME;

Drawable::Drawable() : _mEffectPlay(true) {

}

void Drawable::addEffect(Effects *effect) {
    LOG << Log::VERBOSE << ("[Drawable::addEffect] Effect " +  effect->getType() + " added").c_str() << std::endl;
    mEffects.push_back(effect);
}


void Drawable::setOriginCenter() {
    setOrigin(Vect2f(getSize().x/2, getSize().y/2));
}

void Drawable::setOpacity(float opacity) {
    if (opacity > 1.0f) {
        opacity = 1.0f;
    }

    if (opacity < 0.0f) {
        opacity = 0.0f;
    }

    float alphaOpacity = 255.0f * opacity;
    setColor(Color(getColor().red, getColor().green, getColor().blue,  static_cast<int>(alphaOpacity)));
}

float Drawable::getOpacity() {
    Color tmpColor = getColor();
    return static_cast<float>(tmpColor.alpha / 255.0f);
}

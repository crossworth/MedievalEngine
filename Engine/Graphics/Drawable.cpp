#include "Drawable.h"
#include <Effects/Effects.h>

using namespace ME;

Drawable::Drawable() : mIsEffectPlaying(true) {

}

void Drawable::addEffect(Effects *effect) {
    LOG << Log::VERBOSE << ("[Drawable::addEffect] Effect " +
                            effect->getTypeStd() + " added").c_str() << std::endl;
    mEffects.push_back(effect);
}

void Drawable::setOriginCenter() {
    setOrigin(Vect2f(getSize().x/2, getSize().y/2));
}

void Drawable::playEffects() {
    mIsEffectPlaying = true;

    std::vector<Effects*>::iterator it = mEffects.begin();

    for(int i = 0 ; i < mEffects.size(); i++) {
        (*it)->resetClock();
        it++;
    }
}

bool Drawable::isPlayingEffects() {
    return mIsEffectPlaying;
}

void Drawable::pauseEffects() {
    mIsEffectPlaying = false;
}

void Drawable::removeEffect(std::string effectType) {
    std::vector<Effects*>::iterator it = mEffects.begin();

    for(int i = 0 ; i < mEffects.size(); i++) {
        if ((*it)->getTypeStd() == effectType) {
            LOG << Log::VERBOSE << ("[Drawable::removeEffect] Effect " +
                                    effectType + " removed").c_str() << std::endl;
            (*it)->setDone();
            delete *it;
            mEffects.erase(it);
            it++;
        }
    }
}

void Drawable::removeAllEffects() {
    std::vector<Effects*>::iterator it = mEffects.begin();

    for(int i = 0 ; i < mEffects.size(); i++) {
        (*it)->setDone();
        delete *it;
        mEffects.erase(it);
        it++;
    }

    LOG << Log::VERBOSE << "[Drawable::removeAllEffects] All effect removed"
        << std::endl;
}

void Drawable::setOpacity(float opacity) {
    if (opacity > 1.0f) {
        opacity = 1.0f;
    }

    if (opacity < 0.0f) {
        opacity = 0.0f;
    }

    float alphaOpacity = 255.0f * opacity;
    setColor(Color(getColor().red, getColor().green, getColor().blue,
                   static_cast<int>(alphaOpacity)));
}

float Drawable::getOpacity() {
    Color tmpColor = getColor();
    return static_cast<float>(tmpColor.alpha / 255.0f);
}

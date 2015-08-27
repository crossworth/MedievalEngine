#include "Drawable.h"
#include "Effects/Effect.h"

using namespace ME;

Drawable::Drawable() : mIsEffectPlaying(true) {

}

void Drawable::addEffect(Effect* effect) {
    LOG << Log::VERBOSE << Log::getTime()
        << "[Drawable::addEffect] Effect " + effect->getTypeStd() + " added"
        << std::endl;

    mEffects.push_back(EffectPtr(effect));
}

void Drawable::setOriginCenter() {
    setOrigin(Vect2f(getSize().x / 2, getSize().y / 2));
}

void Drawable::playEffects() {
    mIsEffectPlaying = true;

    std::vector<EffectPtr>::iterator it = mEffects.begin();

    for(int i = 0 ; i < mEffects.size(); i++) {
        (*it)->restartClock();
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
    std::vector<EffectPtr>::iterator it = mEffects.begin();

    for(int i = 0 ; i < mEffects.size(); i++) {
        if ((*it)->getTypeStd() == effectType) {
            LOG << Log::VERBOSE << "[Drawable::removeEffect] Effect " + effectType + " removed"
                << std::endl;

            (*it)->setDone();
            mEffects.erase(it);
            it++;
        }
    }
}

void Drawable::removeAllEffects() {
    std::vector<EffectPtr>::iterator it = mEffects.begin();

    for(int i = 0 ; i < mEffects.size(); i++) {
        (*it)->setDone();
        mEffects.erase(it);
        it++;
    }

    LOG << Log::VERBOSE << "[Drawable::removeAllEffects] All effect removed"
        << std::endl;
}

void Drawable::updateEffects() {
    if(isPlayingEffects()) {
        for(int i = 0 ; i < mEffects.size(); i++) {
            mEffects[i]->update(this);
            if (mEffects[i]->isDone()) {
                mEffects.erase(mEffects.begin() + i);
            }
        }
    }
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

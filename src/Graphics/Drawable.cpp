#include "Drawable.h"
#include "Effects/Effect.h"
#include "Graphics/Window.h"

using namespace ME;

Drawable::Drawable() : mIsEffectPlaying(true) {
    mPaddingTop    = 0.0f;
    mPaddingBottom = 0.0f;
    mPaddingRight  = 0.0f;
    mPaddingLeft   = 0.0f;
}

Drawable::~Drawable() {

}

void Drawable::rotate(const float& angle) {
    setRotation(getRotation() + angle);
}

void Drawable::move(const Vect2f& pos) {
    setPosition(Vect2f(getPosition().x + pos.x, getPosition().y + pos.y));
}

void Drawable::addEffect(Effect* effect) {

    // First we verify if the effect it's already added
    // for (unsigned int i = 0; i < mEffects.size(); i++) {
    //     // We compare using the type here since it's a enum and I think it's faster to compare
    //     // enum's than strings using the getTypeStr() method
    //     // IT IS FASTER, Yes, I have compared on a little test and it's 3 times faster
    //     if (mEffects[i]->getType() == effect->getType()) {
    //         LOG << Log::VERBOSE
    //             << "[Drawable::addEffect] Effect already " + effect->getTypeStr() + " added. Wait until it's done"
    //             << std::endl;
    //         return;
    //     }
    // }


    LOG << Log::VERBOSE
        << "[Drawable::addEffect] Effect " + effect->getTypeStr() + " added"
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
        if ((*it)->getTypeStr() == effectType) {
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

    LOG << Log::VERBOSE << "[Drawable::removeAllEffects] All effects were removed"
        << std::endl;
}

void Drawable::updateEffects() {
    if (isPlayingEffects()) {
        for(int i = 0 ; i < mEffects.size(); i++) {
            mEffects[i]->update(this);
            if (mEffects[i]->isDone()) {
                mEffects.erase(mEffects.begin() + i);
            }
        }
    }
}

void Drawable::setOpacity(const float& opacity) {
    float tmpOpacity = opacity;
    
    if (opacity > 1.0f) {
        tmpOpacity = 1.0f;
    }

    if (opacity < 0.0f) {
        tmpOpacity = 0.0f;
    }

    float alphaOpacity = 255.0f * tmpOpacity;
    setColor(Color(getColor().red, getColor().green, getColor().blue,
                   static_cast<int>(alphaOpacity)));
}

float Drawable::getOpacity() {
    Color tmpColor = getColor();
    return static_cast<float>(tmpColor.alpha / 255.0f);
}

void Drawable::setPadding(const float& percent, Padding type) {
    switch (type) {
        case TOP:
            mPaddingTop = percent;
            break;
        case BOTTOM:
            mPaddingBottom = percent;
            break;
        case LEFT:
            mPaddingLeft = percent;
            break;
        case RIGHT:
            mPaddingRight = percent;
            break;
        default:
            mPaddingTop    = percent;
            mPaddingBottom = percent;
            mPaddingLeft   = percent;
            mPaddingRight  = percent;
    }
}

Vect2f Drawable::getOriginRelative() {
    Vect2f origin(0.0f, 0.0f);

    origin.x = (getSize().x / getGlobalBounds().width) * getOrigin().x;
    origin.y = (getSize().y / getGlobalBounds().height) * getOrigin().y;

    return origin;
}

void Drawable::setRenderState(sf::RenderStates renderState) {
    mRenderStates = renderState;
}


sf::RenderStates* Drawable::getRenderState() {
    return &mRenderStates;
}
#include "SpriteAnimation.h"

using namespace ME;

SpriteAnimation::SpriteAnimation() {
    mType      = "sprite_animation";
    mIsPlaying = true;
}

SpriteAnimation::~SpriteAnimation() {
    // TODO: delete memore allocated
}

void SpriteAnimation::move(const Vect2f &pos) {
    mSprite.move(pos.x, pos.y);
}

float SpriteAnimation::getRotation() {
    return mSprite.getRotation();
}

void SpriteAnimation::setRotation(const float &angle) {
    mSprite.setRotation(angle);
}

void SpriteAnimation::rotate(const float &angle) {
    mSprite.rotate(angle);
}

Vect2f SpriteAnimation::getOrigin() {
    return Vect2f(mSprite.getOrigin().x, mSprite.getOrigin().y);
}

void SpriteAnimation::setOrigin(const Vect2f &origin) {
    mSprite.setOrigin(origin.x, origin.y);
}

void SpriteAnimation::addFrame(const int32_t &time, Texture *texture) {
    mFrames.push_back(std::make_pair(time, texture));
    mFrameIterator = mFrames.begin();

    mSprite.setTexture(*mFrameIterator->second->getResourcePointer());
}

void SpriteAnimation::play() {
    mIsPlaying = true;
}

void SpriteAnimation::pause() {
    mIsPlaying = false;
}

bool SpriteAnimation::isPlaying() {
    return mIsPlaying;
}

void SpriteAnimation::draw(sf::RenderWindow *renderWindow) {
    if(_mEffectPlay) {

        for(int i = 0 ; i < mEffects.size(); i++) {
            mEffects[i]->update(this);

            if (mEffects[i]->done()) {
                // Call Lua Function done effects?
                mEffects.erase(mEffects.begin() + i);
            }
        }
    }

    renderWindow->draw(mSprite);

    if (isPlaying() && mClock.getTime() > mFrameIterator->first) {
        mFrameIterator++;

        if (mFrameIterator == mFrames.end()) {
            mFrameIterator = mFrames.begin();
        }

        mSprite.setTexture(*mFrameIterator->second->getResourcePointer());
        mClock.restart();

    }
}

void SpriteAnimation::setPosition(const Vect2f &pos) {
    mSprite.setPosition(pos.x, pos.y);
}

Vect2f SpriteAnimation::getPosition() {
    return Vect2f(mSprite.getPosition().x, mSprite.getPosition().y);
}

void SpriteAnimation::setSize(const Vect2f &size) {
    mSprite.setScale(size.x / getSize().x, size.y / getSize().y);
}

Vect2f SpriteAnimation::getSize() {
    Vect2f size;
    size.x = mSprite.getGlobalBounds().width;
    size.y = mSprite.getGlobalBounds().height;
    return size;
}

void SpriteAnimation::setScale(const Vect2f &scale) {
    mSprite.setScale(sf::Vector2f(scale.x, scale.y));
}

Vect2f SpriteAnimation::getScale() {
    return Vect2f(mSprite.getScale().x, mSprite.getScale().y);
}

void SpriteAnimation::setColor(const Color &color) {
    sf::Color mColor(color.red, color.green, color.blue, color.alpha);
    mSprite.setColor(mColor);
}

Color SpriteAnimation::getColor() {
    sf::Color mColor = mSprite.getColor();
    return Color(mColor.r, mColor.g, mColor.b, mColor.a);
}

Area SpriteAnimation::getLocalBounds() {
    return Area(mSprite.getLocalBounds().left, mSprite.getLocalBounds().top, mSprite.getLocalBounds().width, mSprite.getLocalBounds().height);
}

Area SpriteAnimation::getGlobalBounds() {
    return Area(mSprite.getGlobalBounds().left, mSprite.getGlobalBounds().top, mSprite.getGlobalBounds().width, mSprite.getGlobalBounds().height);
}

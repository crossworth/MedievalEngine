#include "SpriteAnimation.h"

using namespace ME;

SpriteAnimation::SpriteAnimation() {
    mType = "sprite_animation";
}

void SpriteAnimation::addFrame(const int32_t &time, Texture *texture) {
    mFrames.push_back(std::make_pair(time, texture));
    mFramesIT = mFrames.begin();

    mSprite.setTexture(*mFramesIT->second->getResourcePointer());
}

void SpriteAnimation::draw(sf::RenderWindow *renderWindow) {
    renderWindow->draw(mSprite);

    if (sf::Time(mClock.getElapsedTime()).asMilliseconds() > mFramesIT->first) {
        mFramesIT++;

        if (mFramesIT == mFrames.end()) {
            mFramesIT = mFrames.begin();
        }

        mSprite.setTexture(*mFramesIT->second->getResourcePointer());
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
    mSprite.setScale(size.x/getSize().x, size.y/getSize().y);
}

Vect2f SpriteAnimation::getSize() {
    Vect2f size;
    size.x = mSprite.getGlobalBounds().width;
    size.y = mSprite.getGlobalBounds().height;
    return size;
}

void SpriteAnimation::setColor(const Color &color) {
    sf::Color mColor(color.red, color.green, color.blue, color.alpha);
    mSprite.setColor(mColor);
}

Color SpriteAnimation::getColor() {
    sf::Color mColor = mSprite.getColor();
    return Color(mColor.r, mColor.g, mColor.b, mColor.a);
}

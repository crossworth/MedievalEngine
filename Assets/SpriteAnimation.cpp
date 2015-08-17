#include "SpriteAnimation.h"

using namespace ME;

SpriteAnimation::SpriteAnimation() {
    mType      = "sprite_animation";
    _isPlaying = true;
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
    mFramesIT = mFrames.begin();

    mSprite.setTexture(*mFramesIT->second->getResourcePointer());
}

void SpriteAnimation::play() {
    _isPlaying = true;
}

void SpriteAnimation::pause() {
    _isPlaying = false;
}

bool SpriteAnimation::isPlaying() {
    return _isPlaying;
}

void SpriteAnimation::draw(sf::RenderWindow *renderWindow) {
    if(_mEffectPlay) {
        std::vector<Effects*>::iterator it = mEffects.begin();

        for(int i = 0 ; i < mEffects.size(); i++) {
            (*it)->update(this);

            if ((*it)->done()) {
                // Call Lua Function done effects?
                delete *it;
                mEffects.erase(it);
            }
            it++;
        }
    }

    renderWindow->draw(mSprite);

    if (isPlaying() && sf::Time(mClock.getElapsedTime()).asMilliseconds() > mFramesIT->first) {
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

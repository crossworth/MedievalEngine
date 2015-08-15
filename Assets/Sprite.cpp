#include "Sprite.h"

using namespace ME;

Sprite::Sprite() : mSprite() {
    mType = "sprite";
}

void Sprite::setTexture(Texture *texture) {
    mSprite.setTexture(*texture->getResourcePointer());
}

void Sprite::draw(sf::RenderWindow *renderWindow) {
    if (_mEffectPlay) {
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
}

void Sprite::move(const Vect2f &pos) {
    mSprite.move(pos.x, pos.y);
}

float Sprite::getRotation() {
    return mSprite.getRotation();
}

void Sprite::setRotation(const float &angle) {
    mSprite.setRotation(angle);
}

void Sprite::rotate(const float &angle) {
    mSprite.rotate(angle);
}

Vect2f Sprite::getOrigin() {
    return Vect2f(mSprite.getOrigin().x, mSprite.getOrigin().y);
}

void Sprite::setOrigin(const Vect2f &origin) {
    mSprite.setOrigin(origin.x, origin.y);
}

void Sprite::setPosition(const Vect2f &pos) {
    mSprite.setPosition(pos.x, pos.y);
}

Vect2f Sprite::getPosition() {
    return Vect2f(mSprite.getPosition().x, mSprite.getPosition().y);
}

void Sprite::setSize(const Vect2f &size) {
    mSprite.setScale(size.x/getSize().x, size.y/getSize().y);
}

Vect2f Sprite::getSize() {
    Vect2f size;
    size.x = mSprite.getGlobalBounds().width;
    size.y = mSprite.getGlobalBounds().height;
    return size;
}

void Sprite::setColor(const Color &color) {
    sf::Color mColor(color.red, color.green, color.blue, color.alpha);
    mSprite.setColor(mColor);
}

Color Sprite::getColor() {
    sf::Color mColor = mSprite.getColor();
    return Color(mColor.r, mColor.g, mColor.b, mColor.a);
}

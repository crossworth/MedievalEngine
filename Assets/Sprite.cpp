#include "Sprite.h"

using namespace ME;

Sprite::Sprite() : mSprite() {
    mType = "sprite";
}

void Sprite::setTexture(Texture *texture) {
    mSprite.setTexture(*texture->getResourcePointer());
}

sf::Drawable* Sprite::getObject() {
    return &mSprite;
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

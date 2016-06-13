#include "Sprite.h"
#include "Graphics/Window.h"

using namespace ME;

Sprite::Sprite() : mSprite() {
    mType = Resource::Type::SPRITE;
}

sf::Sprite* Sprite::getResourcePointer() {
    return &mSprite;
}

void Sprite::setTexture(Texture *texture) {
    mIsValid = true;
    mSprite.setTexture(*texture->getResourcePointer());
}

void Sprite::draw(Window& window) {
    updateEffects();
    window.getWindowPtr()->draw(mSprite, mRenderStates);
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
    mSprite.setScale(size.x/getLocalBounds().width, size.y/getLocalBounds().height);
}

Vect2f Sprite::getSize() {
    Vect2f size;
    size.x = mSprite.getGlobalBounds().width;
    size.y = mSprite.getGlobalBounds().height;
    return size;
}

void Sprite::setScale(const Vect2f &scale) {
    mSprite.setScale(sf::Vector2f(scale.x, scale.y));
}

Vect2f Sprite::getScale() {
    return Vect2f(mSprite.getScale().x, mSprite.getScale().y);
}

void Sprite::setColor(const Color &color) {
    sf::Color mColor(color.red, color.green, color.blue, color.alpha);
    mSprite.setColor(mColor);
}

Color Sprite::getColor() {
    sf::Color mColor = mSprite.getColor();
    return Color(mColor.r, mColor.g, mColor.b, mColor.a);
}

Area Sprite::getLocalBounds() {
    return Area(mSprite.getLocalBounds().left, mSprite.getLocalBounds().top,
                mSprite.getLocalBounds().width, mSprite.getLocalBounds().height);
}

Area Sprite::getGlobalBounds() {
    return Area(mSprite.getGlobalBounds().left, mSprite.getGlobalBounds().top,
                mSprite.getGlobalBounds().width, mSprite.getGlobalBounds().height);
}

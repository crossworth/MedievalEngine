#include "ButtonObject.h"
#include <Effects/Fade.h>

using namespace ME;

ButtonObject::ButtonObject(const std::wstring& text, Vect2f pos,  MEid fontID) : _doneTransition(false),
colorGradient1(235, 235, 235), colorGradient2(208, 208, 210), colorGradientHover(246, 246, 246),
c1(colorGradient1.red, colorGradient1.green, colorGradient1.blue), c2(colorGradient2.red, colorGradient2.green, colorGradient2.blue) {


    if (fontID == 0) {
        mTextID  = mAssets->createText(text, 22, defaultFontID);
    }else {
        mTextID  = mAssets->createText(text, 22, fontID);
    }
    mTextRef = mAssets->getAsset<Text>(mTextID);

    float width = 80.0f;

    if (mTextRef->getSize().x > 75.f) {
        width = mTextRef->getSize().x + 20.0f;
    }

    mShapeID  = mAssets->createShape(Vect2f(width, 30.0f), Color(0, 0, 0), pos);
    mShapeRef = mAssets->getAsset<Shape>(mShapeID);

    mTextRef->setOriginCenter();
    mTextRef->setPosition(Vect2f(mShapeRef->getPosition().x+(mShapeRef->getSize().x/2), mShapeRef->getPosition().y+(mTextRef->getSize().y/2)));

    mTextRef->setColor(Color(0, 0, 0));

}

void ButtonObject::draw(Window &window) {
    Area mArea = mShapeRef->getLocalBounds();

    sf::Vertex rectangle[] = {
        sf::Vertex(sf::Vector2f(getPosition().x, getPosition().y), c1),
        sf::Vertex(sf::Vector2f(mArea.width  + getPosition().x, getPosition().y), c1),
        sf::Vertex(sf::Vector2f(mArea.width + getPosition().x, mArea.height + getPosition().y), c2),
        sf::Vertex(sf::Vector2f(getPosition().x, mArea.height + getPosition().y), c2),
    };

    window.getWindowPtr()->draw(rectangle, 4, sf::Quads);


    window.draw(mTextRef);
}

void ButtonObject::update() {

}

void ButtonObject::handleEvents(Event evt) {

}

void ButtonObject::onMouseOver() {
    c2.r = colorGradientHover.red;
    c2.g = colorGradientHover.green;
    c2.b = colorGradientHover.blue;
}

void ButtonObject::onMouseOut() {
    c2.r = colorGradient2.red;
    c2.g = colorGradient2.green;
    c2.b = colorGradient2.blue;
}

void ButtonObject::onClick() {
    c1 = sf::Color::White;
    c2 = sf::Color::White;
}

void ButtonObject::setPosition(const Vect2f &pos) {
    mShapeRef->setPosition(pos);
    mTextRef->setPosition(Vect2f(mShapeRef->getPosition().x+(mShapeRef->getSize().x/2), mShapeRef->getPosition().y+(mTextRef->getSize().y/2)));
}

Vect2f ButtonObject::getPosition() {
    return mShapeRef->getPosition();
}

Vect2f ButtonObject::getSize() {
    return mShapeRef->getSize();
}

void ButtonObject::setOpacity(const float &opacity) {
    mShapeRef->setOpacity(opacity);
    mTextRef->setOpacity(opacity);
}

float ButtonObject::getOpacity() {
    return mShapeRef->getOpacity();
}

void ButtonObject::setColor(const Color &color) {
    mShapeRef->setColor(color);
}

Color ButtonObject::getColor() {
    return mShapeRef->getColor();
}

Area ButtonObject::getLocalBounds() {
    return mShapeRef->getLocalBounds();
}

Area ButtonObject::getGlobalBounds() {
    return mShapeRef->getGlobalBounds();
}


#include "ButtonObject.h"

using namespace ME;

ButtonObject::ButtonObject(const std::wstring& text, Vect2f pos,  MEid fontID) {

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
    mShapeRef->setColor(ColorGradient(Color::BUTTON_C1, Color::BUTTON_C2));

    mTextRef->setOriginCenter();
    mTextRef->setPosition(Vect2f(mShapeRef->getPosition().x+(mShapeRef->getSize().x/2), mShapeRef->getPosition().y+(mTextRef->getSize().y/2)));

    mTextRef->setColor(Color(0, 0, 0));

}

void ButtonObject::draw(Window &window) {
    window.draw(mShapeRef);
    window.draw(mTextRef);
}

void ButtonObject::update() {

}

void ButtonObject::handleEvents(Event evt) {

}

void ButtonObject::onMouseOver() {
    mShapeRef->setColor(ColorGradient(Color::BUTTON_C1, Color::BUTTON_C2));
}

void ButtonObject::onMouseOut() {
    mShapeRef->setColor(ColorGradient(Color::BUTTON_C1, Color::BUTTON_C3));
}

void ButtonObject::onClick() {
    mShapeRef->setColor(Color(Color::WHITE));
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


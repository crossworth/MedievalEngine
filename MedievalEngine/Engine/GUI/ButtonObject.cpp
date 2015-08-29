#include "ButtonObject.h"

using namespace ME;

ButtonObject::ButtonObject(const std::wstring& text, Vect2f pos,  ResourceID fontID) {
    mType   = "button";
    mText   = text;
    mPos    = pos;
    mFontID = fontID;
}

void ButtonObject::init() {
    if (mFontID == 0) {
        mTextID  = mAssets->createText(mText, 22, mDefaultFontID);
    }else {
        mTextID  = mAssets->createText(mText, 22, mFontID);
    }
    mTextRef = mAssets->getResource<Text>(mTextID);

    float width = 80.0f;

    if (mTextRef->getSize().x > 75.f) {
        width = mTextRef->getSize().x + 20.0f;
    }

    mShapeID  = mAssets->createShape(Vect2f(width, 30.0f), Color(0, 0, 0), mPos);
    mShapeRef = mAssets->getResource<Shape>(mShapeID);
    mShapeRef->setColor(ColorGradient(Color::BUTTON_C1, Color::BUTTON_C2));
    mShapeRef->setRadius(2.0f);

    mTextRef->setOriginCenter();
    mTextRef->setPosition(
                Vect2f(mShapeRef->getPosition().x+(mShapeRef->getSize().x/2),
                       mShapeRef->getPosition().y+(mTextRef->getSize().y/2)));

    mTextRef->setColor(Color::BLACK);
}

void ButtonObject::draw(Window& window) {
    window.draw(mShapeRef);
    window.draw(mTextRef);
}

void ButtonObject::update() {

}

void ButtonObject::handleEvents(Event evt, Window& window) {

}

void ButtonObject::onMouseOver(Event evt, Window& window) {
    mShapeRef->setColor(ColorGradient(Color::BUTTON_C1, Color::BUTTON_C2));
    mTextRef->setColor(Color::BLACK);
}

void ButtonObject::onMouseOut(Event evt, Window& window) {
    mShapeRef->setColor(ColorGradient(Color::BUTTON_C1, Color::BUTTON_C3));
    mTextRef->setColor(Color::BLUE);
}

void ButtonObject::onClick(Event evt, Window& window) {
    mShapeRef->setColor(Color::BLUE_VIOLET);
    mTextRef->setColor(Color::WHITE);
}

void ButtonObject::setPosition(const Vect2f& pos) {
    mShapeRef->setPosition(pos);
    mTextRef->setPosition(
                Vect2f(mShapeRef->getPosition().x+(mShapeRef->getSize().x/2),
                       mShapeRef->getPosition().y+(mTextRef->getSize().y/2)));
}

Vect2f ButtonObject::getPosition() {
    return mShapeRef->getPosition();
}

Vect2f ButtonObject::getSize() {
    return mShapeRef->getSize();
}

void ButtonObject::setOpacity(const float& opacity) {
    mShapeRef->setOpacity(opacity);
    mTextRef->setOpacity(opacity);
}

float ButtonObject::getOpacity() {
    return mShapeRef->getOpacity();
}

void ButtonObject::setColor(const Color& color) {
    mShapeRef->setColor(color);
}

Color ButtonObject::getColor() {
    return mShapeRef->getColor();
}

void ButtonObject::setColor(const ColorGradient& color) {
    mShapeRef->setColor(color);
}

ColorGradient ButtonObject::getColorGradient() {
    return mShapeRef->getColorGradient();
}

bool ButtonObject::isColorGradient() {
    return mShapeRef->isColorGradient();
}

void ButtonObject::setTextColor(const Color& color) {
    mTextRef->setColor(color);
}

Color ButtonObject::getTextColor() {
    return mTextRef->getColor();
}

Area ButtonObject::getLocalBounds() {
    return mShapeRef->getLocalBounds();
}

Area ButtonObject::getGlobalBounds() {
    return mShapeRef->getGlobalBounds();
}

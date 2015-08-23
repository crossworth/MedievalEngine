#include "TextObject.h"

using namespace ME;

TextObject::TextObject(const std::wstring& text, const int& textSize, const Vect2f& pos) {
    mType     = "text";
    mPos      = pos;
    mText     = text;
    mTextSize = textSize;
}

void TextObject::init() {
    mTextID  = mAssets->createText(mText, mTextSize, mDefaultFontID);
    mTextRef = mAssets->getAsset<Text>(mTextID);
    setPosition(mPos);
}

void TextObject::setPosition(const Vect2f& pos) {
    mTextRef->setPosition(pos);
}

Vect2f TextObject::getPosition() {
    return mTextRef->getPosition();
}

Vect2f TextObject::getSize() {
    return mTextRef->getSize();
}

void TextObject::onMouseOver(Event evt, Window& window) {

}

void TextObject::onClick(Event evt, Window& window) {

}

void TextObject::onMouseOut(Event evt, Window& window) {

}

void TextObject::setOpacity(const float& opacity) {
    mTextRef->setOpacity(opacity);
}

float TextObject::getOpacity() {
    return mTextRef->getOpacity();
}

void TextObject::setColor(const Color& color) {
    mTextRef->setColor(color);
}

Color TextObject::getColor() {
    return mTextRef->getColor();
}

Area TextObject::getLocalBounds() {
    return mTextRef->getLocalBounds();
}

Area TextObject::getGlobalBounds() {
    return mTextRef->getGlobalBounds();
}

void TextObject::draw(Window& window) {
    if (mIsVisible) {
        window.draw(mTextRef);
    }
}

void TextObject::update() {
    if (mIsActive) {

    }
}

void TextObject::handleEvents(Event evt, Window& window) {

}

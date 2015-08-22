#include "TextObject.h"

using namespace ME;

TextObject::TextObject(const std::wstring& text, const int& textSize) {
    mType = "text";

    MEid mFont = mAssets->loadFont("font/YanoneKaffeesatz-Regular.ttf");
    mTextID    = mAssets->createText(text, textSize, mFont);
    mTextRef   = mAssets->getAsset<Text>(mTextID);

    setPosition(Vect2f(100.f, 100.f));
}

void TextObject::setPosition(const Vect2f &pos) {
    mTextRef->setPosition(pos);
}

Vect2f TextObject::getPosition() {
    return mTextRef->getPosition();
}

Vect2f TextObject::getSize() {
    return mTextRef->getSize();
}

void TextObject::onMouseOver() {

}

void TextObject::onClick() {

}

void TextObject::onMouseOut() {

}

void TextObject::setOpacity(const float &opacity) {
    mTextRef->setOpacity(opacity);
}

float TextObject::getOpacity() {
    return mTextRef->getOpacity();
}

void TextObject::setColor(const Color &color) {
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

void TextObject::draw(Window &window) {
    if (mIsVisible) {
        window.draw(mTextRef);
    }
}

void TextObject::update() {
    if (mIsActive) {

    }
}

void TextObject::handleEvents(Event evt) {

}

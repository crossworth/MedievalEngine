#include "TextWidget.h"

using namespace ME;

TextWidget::TextWidget(const sf::String& text,
                       const int& textSize,
                       const Vect2f& pos, 
                       const ResourceID& fontID) {
    mType        = "TextWidget";
    mPos         = pos;
    mText        = text;
    mTextSize    = textSize;
    mIsMouseOver = false;
    mFontID      = fontID;

}

void TextWidget::setFont(const ResourceID& fontID) {
    mFontID = fontID;
}

ResourceID TextWidget::getFont() {
    if (mFontID != 0) {
        return mFontID;
    } else {
        return mDefaultFontID;
    }
}

void TextWidget::init() {
    ResourceID textFont = mDefaultFontID;

    if (mFontID != 0) {
        textFont = mFontID;
    }

    mTextID  = mResources->createText(mText, mTextSize, textFont);
    mTextRef = mResources->getResource<Text>(mTextID);
    setPosition(mPos);
}

void TextWidget::setPosition(const Vect2f& pos) {
    mTextRef->setPosition(pos);
}

Vect2f TextWidget::getPosition() {
    return mTextRef->getPosition();
}

Vect2f TextWidget::getSize() {
    return mTextRef->getSize();
}

void TextWidget::setOpacity(const float& opacity) {
    mTextRef->setOpacity(opacity);
}

float TextWidget::getOpacity() {
    return mTextRef->getOpacity();
}

void TextWidget::setColor(const Color& color) {
    mTextRef->setColor(color);
}

Color TextWidget::getColor() {
    return mTextRef->getColor();
}

Area TextWidget::getLocalBounds() {
    return mTextRef->getLocalBounds();
}

Area TextWidget::getGlobalBounds() {
    return mTextRef->getGlobalBounds();
}

void TextWidget::draw(Window& window) {
    if (mIsVisible) {
        window.draw(mTextRef);
    }
}

void TextWidget::update() {
    // if (mIsActive) {

    // }
}

void TextWidget::handleEvents(Event evt) {

        Vect2i mousePos = Mouse::getPosition(getWindow());

        if (getGlobalBounds().contains(mousePos)) {
            mIsMouseOver = true;
            notify(GUIEvent::Type::onMouseOver, this);
        }

        if (getGlobalBounds().contains(mousePos) && Mouse::isButtonPressed(Mouse::Button::Left)) {
            notify(GUIEvent::Type::onClick, this);   
        }

        if (!(getGlobalBounds().contains(mousePos)) && mIsMouseOver) {
            mIsMouseOver = false;
            notify(GUIEvent::Type::onMouseOut, this);
        }
}

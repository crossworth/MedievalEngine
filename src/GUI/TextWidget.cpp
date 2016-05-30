#include "TextWidget.h"


using namespace ME;

TextWidget::TextWidget(const String& text,
                       const int& textSize,
                       const Vect2f& pos,
                       const ResourceID& fontID) {
    mType        = "TextWidget";
    mPos         = pos;
    mText        = text;
    mTextSize    = textSize;
    mIsMouseOver = false;
    mFontID      = fontID;
    mTextRef     = nullptr;

}

void TextWidget::setFont(const ResourceID& fontID) {
    mFontID = fontID;

    if (mTextRef != nullptr) {
        mTextRef->setFont(*mResources->getResource<Font>(mFontID));
    }
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

void TextWidget::setSize(const Vect2f& size) {
    mTextRef->setSize(size);
}

void TextWidget::setScale(const Vect2f& scale) {
    mTextRef->setScale(scale);
}

Vect2f TextWidget::getScale() {
    return mTextRef->getScale();
}

float TextWidget::getRotation() {
    return mTextRef->getRotation();
}

void TextWidget::setRotation(const float& angle) {
    mTextRef->setRotation(angle);
}

Vect2f TextWidget::getOrigin() {
    return mTextRef->getOrigin();
}

void TextWidget::setOrigin(const Vect2f& origin) {
    mTextRef->setOrigin(origin);
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
        updateEffects();
        mTextRef->setRenderState(mRenderStates);
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

    if (getGlobalBounds().contains(mousePos) && evt.type == Event::MouseButtonReleased &&
        evt.mouseButton.button == Mouse::Button::Left) {
        notify(GUIEvent::Type::onClick, this);
    }

    if (!(getGlobalBounds().contains(mousePos)) && mIsMouseOver) {
        mIsMouseOver = false;
        notify(GUIEvent::Type::onMouseOut, this);
    }
}

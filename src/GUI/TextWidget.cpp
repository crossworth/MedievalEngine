#include "TextWidget.h"


using namespace ME;

TextWidget::TextWidget(const String &text,
                       const int &textSize,
                       const Vect2f &pos,
                       const std::string &fontName) {
    mType        = "TextWidget";
    mPos         = pos;
    mText        = text;
    mTextSize    = textSize;
    mIsMouseOver = false;
    mFontName    = fontName;
    mTextRef     = nullptr;

}

void TextWidget::setFont(const std::string &fontName) {
    mFontName = fontName;

    if (mTextRef != nullptr) {
        mTextRef->setFont(*ResourceManager::get<Font>(mFontName));
    }
}

std::string TextWidget::getFont() {
    return mFontName;
}

void TextWidget::init() {
    if (mFontName == "") {
        mFontName = "game_font";
    }

    std::string textWidgetName = std::string("text_widget_" + mText);

    ResourceManager::createText(textWidgetName, mText, mTextSize, mFontName);
    mTextRef = ResourceManager::get<Text>(textWidgetName);
    setPosition(mPos);
}

void TextWidget::setPosition(const Vect2f &pos) {
    mTextRef->setPosition(pos);
}

Vect2f TextWidget::getPosition() {
    return mTextRef->getPosition();
}

Vect2f TextWidget::getSize() {
    return mTextRef->getSize();
}

void TextWidget::setSize(const Vect2f &size) {
    mTextRef->setSize(size);
}

void TextWidget::setScale(const Vect2f &scale) {
    mTextRef->setScale(scale);
}

Vect2f TextWidget::getScale() {
    return mTextRef->getScale();
}

float TextWidget::getRotation() {
    return mTextRef->getRotation();
}

void TextWidget::setRotation(const float &angle) {
    mTextRef->setRotation(angle);
}

Vect2f TextWidget::getOrigin() {
    return mTextRef->getOrigin();
}

void TextWidget::setOrigin(const Vect2f &origin) {
    mTextRef->setOrigin(origin);
}

void TextWidget::setOpacity(const float &opacity) {
    mTextRef->setOpacity(opacity);
}

float TextWidget::getOpacity() {
    return mTextRef->getOpacity();
}

void TextWidget::setColor(const Color &color) {
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

void TextWidget::draw(Window &window) {
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

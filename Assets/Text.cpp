#include "Text.h"

using namespace ME;

Text::Text() {
    mType = "text";
}

void Text::setFont(Font &font) {
    mText.setFont(*font.getResourcePointer());
}

void Text::setFontSize(const unsigned int &size) {
    mText.setCharacterSize(size);
}

void Text::setString(const std::string &text) {
    mText.setString(text);
}

void Text::setTextShadow(const float &factor, const Color &color) {
    _hasTextShadow    = true;
    mTextShadow       = color;
    mTextShadowFactor = factor;
}

void Text::removeTextShadow() {
    _hasTextShadow = false;
}

void Text::setStyle(const FONT_STYLE &style) {
    switch (style) {
    case REGULAR:
        mText.setStyle(sf::Text::Style::Regular);
        break;
    case BOLD:
        mText.setStyle(sf::Text::Style::Bold);
        break;
    case ITALIC:
        mText.setStyle(sf::Text::Style::Italic);
        break;
    case UNDERLINE:
        mText.setStyle(sf::Text::Style::Underlined);
        break;
    default:
        break;
    }
}

void Text::draw(sf::RenderWindow *renderWindow) {
    if (_hasTextShadow) {
        Color tmpColor = getColor();
        Vect2f tmpPos  = getPosition();

        setColor(mTextShadow);
        setPosition(Vect2f(getPosition().x, getPosition().y + mTextShadowFactor));

        renderWindow->draw(mText);

        setColor(tmpColor);
        setPosition(tmpPos);
    }

    renderWindow->draw(mText);
}

void Text::setPosition(const Vect2f &pos) {
    mText.setPosition(pos.x, pos.y);
}

Vect2f Text::getPosition() {
    return Vect2f(mText.getPosition().x, mText.getPosition().y);
}

void Text::setSize(const Vect2f &size) {
    mText.setScale(size.x/getSize().x, size.y/getSize().y);
}

Vect2f Text::getSize() {
    Vect2f size;
    size.x = mText.getGlobalBounds().width;
    size.y = mText.getGlobalBounds().height;
    return size;
}

void Text::setColor(const Color &color) {
    sf::Color mColor(color.red, color.green, color.blue, color.alpha);
    mText.setColor(mColor);
}

Color Text::getColor() {
    sf::Color mColor = mText.getColor();
    return Color(mColor.r, mColor.g, mColor.b, mColor.a);
}


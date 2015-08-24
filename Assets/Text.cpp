#include "Text.h"

using namespace ME;

Text::Text() {
    mType = "text";
}

std::string Text::getString() {
    return mText.getString();
}

unsigned int Text::getFontSize() {
    return mText.getCharacterSize();
}

Text::FONT_STYLE Text::getStyle() {
    switch (mText.getStyle()) {
    case sf::Text::Style::Bold:
        return Text::BOLD;
        break;
    case sf::Text::Style::Regular:
        return Text::REGULAR;
        break;
    case sf::Text::Style::Underlined:
        return Text::UNDERLINE;
        break;
    case sf::Text::Style::Italic:
        return Text::ITALIC;
        break;
    }
}

void Text::setFont(Font &font) {
    mText.setFont(*font.getResourcePointer());
}

void Text::setFontSize(const unsigned int &size) {
    mText.setCharacterSize(size);
}

void Text::setString(const std::wstring &text) {
    mText.setString(text);
}

void Text::setTextShadow(const float &factor, const Color &color) {
    mHasTextShadow    = true;
    mTextShadow       = color;
    mTextShadowFactor = factor;
}

void Text::removeTextShadow() {
    mHasTextShadow = false;
}

bool Text::isTextShadowEnable() {
    return mHasTextShadow;
}

void Text::setStyle(const Text::FONT_STYLE &style) {
    switch (style) {
    case Text::BOLD:
        mText.setStyle(sf::Text::Style::Bold);
        break;
    case Text::ITALIC:
        mText.setStyle(sf::Text::Style::Italic);
        break;
    case Text::UNDERLINE:
        mText.setStyle(sf::Text::Style::Underlined);
        break;
    default:
        mText.setStyle(sf::Text::Style::Regular);
        break;
    }
}

void Text::draw(sf::RenderWindow* renderWindow) {
    if (mHasTextShadow) {
        Color tmpColor    = getColor();
        Vect2f tmpPos     = getPosition();
        mTextShadow.alpha = tmpColor.alpha;

        setColor(mTextShadow);
        setPosition(Vect2f(getPosition().x,
                           getPosition().y + mTextShadowFactor));

        renderWindow->draw(mText);

        setColor(tmpColor);
        setPosition(tmpPos);
    }

    if(mIsEffectPlaying) {
        std::vector<Effects*>::iterator it = mEffects.begin();

        for(int i = 0 ; i < mEffects.size(); i++) {
            (*it)->update(this);

            if ((*it)->done()) {
                // Call Lua Function done effects?
                delete *it;
                mEffects.erase(it);
            }
            it++;
        }
    }

    renderWindow->draw(mText);
}

void Text::move(const Vect2f &pos) {
    mText.move(pos.x, pos.y);
}

float Text::getRotation() {
    return mText.getRotation();
}

void Text::setRotation(const float &angle) {
    mText.setRotation(angle);
}

void Text::rotate(const float &angle) {
    mText.rotate(angle);
}

Vect2f Text::getOrigin() {
    return Vect2f(mText.getOrigin().x, mText.getOrigin().y);
}

void Text::setOrigin(const Vect2f &origin) {
    mText.setOrigin(origin.x, origin.y);
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

void Text::setScale(const Vect2f &scale) {
    mText.setScale(sf::Vector2f(scale.x, scale.y));
}

Vect2f Text::getScale() {
    return Vect2f(mText.getScale().x, mText.getScale().y);
}

void Text::setColor(const Color &color) {
    sf::Color mColor(color.red, color.green, color.blue, color.alpha);
    mText.setColor(mColor);
}

Color Text::getColor() {
    sf::Color mColor = mText.getColor();
    return Color(mColor.r, mColor.g, mColor.b, mColor.a);
}

Area Text::getLocalBounds() {
    return Area(mText.getLocalBounds().left, mText.getLocalBounds().top,
                mText.getLocalBounds().width, mText.getLocalBounds().height);
}

Area Text::getGlobalBounds() {
    return Area(mText.getGlobalBounds().left, mText.getGlobalBounds().top,
                mText.getGlobalBounds().width, mText.getGlobalBounds().height);
}


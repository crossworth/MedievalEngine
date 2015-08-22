#include "TextScrollListObject.h"

using namespace ME;

TextScrollListObject::TextScrollListObject() : mPadding(10.f), mScrollSpeed(2.0f) {
    mType        = "text_scroll_list";
    MEid textID  = mAssets->createText(L"ScrollView", 22, mDefaultFontID);
    MEid shapeID = mAssets->createShape(Vect2f(250.f, 35.f), Color(255, 255, 255, 120), Vect2f(50.f, 500.f));

    mTextRef  = mAssets->getAsset<Text>(textID);
    mShapeRef = mAssets->getAsset<Shape>(shapeID);
    mShapeRef->setRadius(4.f);
    mShapeRef->setColor(Color::BLACK);
    mTextRef->setPosition(Vect2f(mShapeRef->getPosition().x + mPadding, mShapeRef->getPosition().y));
    mTextRef->setColor(Color::WHITE);

    mLineHeight = mTextRef->getSize().y;
    mTextRef->setString(L"");
    mShapeRef->setSize(Vect2f(mShapeRef->getSize().x, mLineHeight + ( 2 * mPadding )));

    setOpacity(0.7);
}

void TextScrollListObject::addText(const std::wstring& text) {
    // Lets see if this work
    mStringBuffer = mStringBuffer +  L"\n" +  text;
    mTextRef->setString(mStringBuffer);
}

void TextScrollListObject::draw(Window& window) {
    WindowInfo* size  = window.getWindowInfo();

    Area mShapeArea = mShapeRef->getGlobalBounds();

    sf::View panelView;
    sf::FloatRect panelRect(mShapeArea.left / size->width, (mShapeArea.top) / size->height, (mShapeArea.width) / size->width, (mShapeArea.height) / size->height);
    panelView.reset(sf::FloatRect(mShapeArea.left, mShapeArea.top, mShapeArea.width, mShapeArea.height));
    panelView.setViewport(panelRect);

    window.draw(mShapeRef);
    window.getWindowPtr()->setView(panelView);
    window.draw(mTextRef);
    window.getWindowPtr()->setView(window.getWindowPtr()->getDefaultView());

}

void TextScrollListObject::update() {
    if (mTextRef->getGlobalBounds().top + mTextRef->getGlobalBounds().height + mPadding >
        mShapeRef->getGlobalBounds().top + mShapeRef->getGlobalBounds().height ) {
        mTextRef->move(Vect2f(0.0f, -mScrollSpeed));
    }
}

void TextScrollListObject::handleEvents(Event evt) {

}

void TextScrollListObject::setSize(const Vect2f& size) {
    mShapeRef->setSize(size);
    mSize = size;
}

void TextScrollListObject::setBackgroundColor(const Color& color) {
    mColor            = color;
    mHasColorGradient = false;
    mShapeRef->setColor(color);
}

void TextScrollListObject::setBackgroundColor(const ColorGradient& color) {
    mColorGradient    = color;
    mHasColorGradient = true;
    mShapeRef->setColor(color);
}

void TextScrollListObject::textColor(const Color& color) {
    mTextColor = color;
    mTextRef->setColor(color);
}

Color TextScrollListObject::getTextColor() {
    return mTextColor;
}

void TextScrollListObject::onClick() {

}

void TextScrollListObject::setOpacity(const float& opacity) {
    mOpacity  = opacity;
    mTextRef->setOpacity(opacity);
    mShapeRef->setOpacity(opacity);
}

Area TextScrollListObject::getLocalBounds() {
    return mShapeRef->getLocalBounds();
}

Area TextScrollListObject::getGlobalBounds() {
    return mShapeRef->getGlobalBounds();
}

Vect2f TextScrollListObject::getSize() {
    return mShapeRef->getSize();
}


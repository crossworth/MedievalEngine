#include "TextScrollListObject.h"

using namespace ME;

TextScrollListObject::TextScrollListObject() : mPadding(10.f), mScrollSpeed(10.0f),
    mMaxiumExpandSize(250.0f, 150.0f) , mEnableTransition(false), mExpandTop(false), mIsExpanded(false),
    mShowScrollBar(false), mScrollBarClicked(false), mScrollBarHasMoved(false), mScrollBarAutoScroll(false) {

    mType         = "text_scroll_list";
    MEid textID   = mAssets->createText(L"ScrollView", 22, mDefaultFontID);
    MEid shapeID  = mAssets->createShape(Vect2f(250.f, 35.f));
    MEid scrollID = mAssets->createShape(Vect2f(8.f, 30.f), Color(0, 0, 0, 75));

    mTextRef   = mAssets->getAsset<Text>(textID);
    mShapeRef  = mAssets->getAsset<Shape>(shapeID);
    mScrollBar = mAssets->getAsset<Shape>(scrollID);

    mShapeRef->setRadius(4.0f);
    mScrollBar->setRadius(3.0f);
    mShapeRef->setPosition(Vect2f(50.f, 550.f));
    mShapeRef->setColor(ColorGradient(Color::BUTTON_C1, Color::BUTTON_C2));

    mTextRef->setPosition(Vect2f(mShapeRef->getPosition().x + mPadding, mShapeRef->getPosition().y));
    mTextRef->setColor(Color::BLACK);

    mLineHeight = mTextRef->getSize().y;
    mTextRef->setString(L"");
    mShapeRef->setSize(Vect2f(mShapeRef->getSize().x, mLineHeight + ( 2 * mPadding )));

    mExpandVelocity = 4.f;

}

void TextScrollListObject::addText(const std::wstring& text) {
    // Lets see if this work
    mStringBuffer = mStringBuffer +  L"\n" +  text;
    mTextRef->setString(mStringBuffer);

    if (mTextRef->getSize().y > mShapeRef->getSize().y && mIsExpanded) {
        mShowScrollBar = true;

        float scrollBarHeight = (mShapeRef->getSize().y / mTextRef->getSize().y) * mShapeRef->getSize().y;

        if (scrollBarHeight < 30.f) {
            scrollBarHeight = 30.f;
        }

        mScrollBar->setSize(Vect2f(mScrollBar->getSize().x, scrollBarHeight));

        if (!mScrollBarHasMoved || mScrollBarAutoScroll) {
            mScrollBar->setPosition(Vect2f(mShapeRef->getPosition().x + mShapeRef->getSize().x - mScrollBar->getSize().x - 3.0f,
                        mShapeRef->getPosition().y + mShapeRef->getSize().y - mScrollBar->getSize().y ));;
        }
    }
}

void TextScrollListObject::draw(Window& window) {
    winSize  = window.getWindowInfo();

    Area mShapeArea = mShapeRef->getGlobalBounds();

    sf::View panelView;
    sf::FloatRect panelRect(mShapeArea.left / winSize->width, (mShapeArea.top) / winSize->height, (mShapeArea.width) / winSize->width, (mShapeArea.height) / winSize->height);
    panelView.reset(sf::FloatRect(mShapeArea.left, mShapeArea.top, mShapeArea.width, mShapeArea.height));
    panelView.setViewport(panelRect);

    window.draw(mShapeRef);

    if (mIsExpanded && mShowScrollBar) {
        window.draw(mScrollBar);
    }

    window.getWindowPtr()->setView(panelView);
    window.draw(mTextRef);
    window.getWindowPtr()->setView(window.getWindowPtr()->getDefaultView());

}

void TextScrollListObject::update() {
    // Verify if the scrollbar has been click, if so we dont change the position of the text
    // if the scrollbar has not been changed and the text is overflowing we scroll it
    if ((!mScrollBarHasMoved || mScrollBarAutoScroll ) && mTextRef->getGlobalBounds().top + mTextRef->getGlobalBounds().height + mPadding >
        mShapeRef->getGlobalBounds().top + mShapeRef->getGlobalBounds().height) {
        float diff = mTextRef->getGlobalBounds().top + mTextRef->getGlobalBounds().height + mPadding -
                     mShapeRef->getGlobalBounds().top + mShapeRef->getGlobalBounds().height;
        diff = diff / 100;

        mTextRef->move(Vect2f(0.0f, -((mScrollSpeed / 100) * mClock.getTime() * diff) ));
    }

    if (mEnableTransition) {

        // We are on the bottom of the screen, so we go upwards
        // TODO: Resize box to default
        if (mShapeRef->getPosition().y + mShapeRef->getSize().y + mMaxiumExpandSize.y > winSize->height ) {
            mExpandTop = true;
        }

        if (mShapeRef->getSize().x < mMaxiumExpandSize.x) {
            float diff = (mMaxiumExpandSize.x - mShapeRef->getSize().x) / 10;
            mShapeRef->setSize(Vect2f(mShapeRef->getSize().x + ((mExpandVelocity / 100) * mClock.getTime() * diff), mShapeRef->getSize().y));
        }

        if (mShapeRef->getSize().y < mMaxiumExpandSize.y) {
            float diff = (mMaxiumExpandSize.y - mShapeRef->getSize().y) / 10;
            float pos  = ((mExpandVelocity / 100) * mClock.getTime() * diff);
            mShapeRef->setSize(Vect2f(mShapeRef->getSize().x, mShapeRef->getSize().y + pos));

            if (mExpandTop) {
                mShapeRef->setPosition(Vect2f(mShapeRef->getPosition().x, mShapeRef->getPosition().y - pos));
            } else {
                mTextRef->setPosition(Vect2f(mTextRef->getPosition().x, mTextRef->getPosition().y + pos));
            }
        }

        if (mShapeRef->getSize().x >= mMaxiumExpandSize.x - 1.f && mShapeRef->getSize().y >= mMaxiumExpandSize.y - 1.f) {
            mEnableTransition = false;
            mIsExpanded       = true;
        }
    }

    mClock.restart();
}

void TextScrollListObject::handleEvents(Event evt, Window& window) {

    window.getWindowPtr()->setTitle(std::string(
    Data2::int_to_str(Mouse::getPosition(*window.getWindowPtr()).x)
    + "  " +
    Data2::int_to_str(Mouse::getPosition(*window.getWindowPtr()).y)));

    if (evt.type == Event::MouseButtonReleased) {

        if (evt.mouseButton.button == Mouse::Button::Left && mScrollBarClicked){
            mScrollBarClicked = false;
        }
    }

    if (mScrollBarClicked) {
        mScrollBarHasMoved = true;
        Vect2i mousePos    = Mouse::getPosition(*window.getWindowPtr());

        if (mousePos.y > mShapeRef->getPosition().y + (mScrollBar->getSize().y / 2) && mousePos.y < mShapeRef->getPosition().y + mShapeRef->getSize().y - (mScrollBar->getSize().y / 2)) {
            mScrollBar->setPosition(Vect2f(mScrollBar->getPosition().x, mousePos.y - (mScrollBar->getSize().y / 2)));

            // update text position based on the scrollbar
            float basePosition = mScrollBar->getPosition().y / mTextRef->getSize().y;
            basePosition       = basePosition * mShapeRef->getSize().y;

            mTextRef->setPosition(Vect2f(mTextRef->getPosition().x, basePosition));
            std::cout << mTextRef->getPosition() << std::endl;
        }
    }

}

void TextScrollListObject::setScrollSpeed(float& scrollspeed) {
    mScrollSpeed = scrollspeed;
}

float TextScrollListObject::getScrollSpeed() {
    return mScrollSpeed;
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

void TextScrollListObject::setScrollBarColor(const Color& color) {
    mScrollBar->setColor(color);
    mScrollBarColor = color;
}

Color TextScrollListObject::getScrollBarColor() {
    return mScrollBarColor;
}

void TextScrollListObject::setTextAutoScroll(bool scroll) {
    mScrollBarAutoScroll = scroll;
}

bool TextScrollListObject::isTextAutoScroll() {
    return mScrollBarAutoScroll;
}

void TextScrollListObject::setExpandeSize(const Vect2f& size) {
    mMaxiumExpandSize = size;
}

Vect2f TextScrollListObject::getExpandSize() {
    return mMaxiumExpandSize;
}

void TextScrollListObject::setExpandVelocity(const float& velocity) {
    mExpandVelocity = velocity;
}

float TextScrollListObject::getExpandVelocity() {
    return mExpandVelocity;
}

bool TextScrollListObject::isExpanded() {
    return mIsExpanded;
}

void TextScrollListObject::onClick(Event evt, Window& window) {
    if (!isExpanded()) {
        mEnableTransition = true;
    } else {
        Vect2i mousePos = Mouse::getPosition(*window.getWindowPtr());

        if (mShowScrollBar && mScrollBar->getGlobalBounds().contains(mousePos)) {
            mScrollBarClicked = true;
        }
    }
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

#include "TextListWidget.h"

using namespace ME;

TextListWidget::TextListWidget() : mPadding(10.f), mScrollSpeed(10.0f),
    mMaxiumExpandSize(250.0f, 150.0f) , mEnableTransition(false), mExpandTop(false),
    mIsExpanded(false), mShowScrollBar(false), mScrollBarClicked(false),
    mScrollBarHasMoved(false), mScrollBarAutoScroll(false) {

    mType = "TextListWidget";
}

void TextListWidget::init() {
    ResourceID textID   = mResources->createText("ScrollView", 22, mDefaultFontID);
    ResourceID shapeID  = mResources->createShape(Vect2f(250.f, 35.f));
    ResourceID scrollID = mResources->createShape(Vect2f(8.f, 30.f), Color(0, 0, 0, 75));

    mTextRef      = mResources->getResource<Text>(textID);
    mShapeRef     = mResources->getResource<Shape>(shapeID);
    mScrollBarRef = mResources->getResource<Shape>(scrollID);

    mShapeRef->setRadius(4.0f);
    mScrollBarRef->setRadius(3.0f);

    mShapeRef->setPosition(Vect2f(50.f, 550.f));
    mShapeRef->setColor(ColorGradient(Color::BUTTON_C1, Color::BUTTON_C2));

    mTextRef->setPosition(Vect2f(mShapeRef->getPosition().x + mPadding,
                                 mShapeRef->getPosition().y));
    mTextRef->setColor(Color::BLACK);

    mLineHeight = mTextRef->getSize().y;

    mTextRef->setString("");
    mShapeRef->setSize(Vect2f(mShapeRef->getSize().x,
                              mLineHeight + ( 2 * mPadding )));

    mExpandVelocity = 4.f;
}

void TextListWidget::addText(const sf::String& text) {
    mStringBuffer = mStringBuffer +  "\n" +  text;
    mTextRef->setString(mStringBuffer);

    if (mTextRef->getSize().y > mShapeRef->getSize().y && mIsExpanded) {
        mShowScrollBar = true;

        float scrollBarHeight = (mShapeRef->getSize().y / mTextRef->getSize().y) *
                                 mShapeRef->getSize().y;

        if (scrollBarHeight < 30.f) {
            scrollBarHeight = 30.f;
            // TODO(Pedro): change the position to be relative to the amount of the text that exists
        }

        mScrollBarRef->setSize(Vect2f(mScrollBarRef->getSize().x, scrollBarHeight));

        if (!mScrollBarHasMoved || mScrollBarAutoScroll) {
            mScrollBarRef->setPosition(
                        Vect2f(mShapeRef->getPosition().x + mShapeRef->getSize().x -
                               mScrollBarRef->getSize().x - 3.0f,
                               mShapeRef->getPosition().y + mShapeRef->getSize().y -
                               mScrollBarRef->getSize().y ));
        }
    }
}

void TextListWidget::draw(Window& window) {
    // TODO(Pedro): If its visible
    winSize  = window.getWindowInfo();

    Area mShapeArea = mShapeRef->getGlobalBounds();

    sf::View panelView;
    sf::FloatRect panelRect(mShapeArea.left / winSize->width,
                            (mShapeArea.top) / winSize->height,
                            (mShapeArea.width) / winSize->width,
                            (mShapeArea.height) / winSize->height);

    panelView.reset(sf::FloatRect(mShapeArea.left, mShapeArea.top,
                                  mShapeArea.width, mShapeArea.height));

    panelView.setViewport(panelRect);

    window.draw(mShapeRef);

    if (mIsExpanded && mShowScrollBar) {
        window.draw(mScrollBarRef);
    }

    window.getWindowPtr()->setView(panelView);
    window.draw(mTextRef);
    window.getWindowPtr()->setView(window.getWindowPtr()->getDefaultView());
}

void TextListWidget::update() {
    // TODO(Pedro): If its active

    // Verify if the scrollbar has been click, if so we dont change the position of the text
    // if the scrollbar has not been changed and the text is overflowing we scroll it
    if ((!mScrollBarHasMoved || mScrollBarAutoScroll ) &&
        mTextRef->getGlobalBounds().top + mTextRef->getGlobalBounds().height +
        mPadding > mShapeRef->getGlobalBounds().top + mShapeRef->getGlobalBounds().height) {

        float diff = mTextRef->getGlobalBounds().top +
                     mTextRef->getGlobalBounds().height + mPadding -
                     mShapeRef->getGlobalBounds().top +
                     mShapeRef->getGlobalBounds().height;

        diff = diff / 100;

        mTextRef->move(Vect2f(0.0f, -((mScrollSpeed / 100) * mClock.getTime() * diff) ));
    } else {
        setTextAutoScroll(false);
    }

    if (mEnableTransition) {
        // We are on the bottom of the screen, so we go upwards
        // TODO: Resize box to default
        if (mShapeRef->getPosition().y + mShapeRef->getSize().y +
            mMaxiumExpandSize.y > winSize->height ) {
            mExpandTop = true;
        }

        if (mShapeRef->getSize().x < mMaxiumExpandSize.x) {
            float diff = (mMaxiumExpandSize.x - mShapeRef->getSize().x) / 10;
            mShapeRef->setSize(
                        Vect2f(mShapeRef->getSize().x + ((mExpandVelocity / 100) *
                               mClock.getTime() * diff), mShapeRef->getSize().y));
        }

        if (mShapeRef->getSize().y < mMaxiumExpandSize.y) {
            float diff = (mMaxiumExpandSize.y - mShapeRef->getSize().y) / 10;
            float pos  = ((mExpandVelocity / 100) * mClock.getTime() * diff);

            mShapeRef->setSize(Vect2f(mShapeRef->getSize().x,
                                      mShapeRef->getSize().y + pos));

            if (mExpandTop) {
                mShapeRef->setPosition(Vect2f(mShapeRef->getPosition().x,
                                              mShapeRef->getPosition().y - pos));
            } else {
                mTextRef->setPosition(Vect2f(mTextRef->getPosition().x,
                                             mTextRef->getPosition().y + pos));
            }
        }

        if (mShapeRef->getSize().x >= mMaxiumExpandSize.x - 1.f &&
            mShapeRef->getSize().y >= mMaxiumExpandSize.y - 1.f) {

            mEnableTransition = false;
            mIsExpanded       = true;
        }
    }

    mClock.restart();
}

void TextListWidget::handleEvents(Event evt) {

    if (evt.type == Event::MouseButtonReleased) {
        if (evt.mouseButton.button == Mouse::Button::Left && mScrollBarClicked){
            mScrollBarClicked = false;
        }
    }

    Vect2i mousePos = Mouse::getPosition(getWindow());

    if (isExpanded() && evt.type == Event::MouseWheelScrolled &&
        mShapeRef->getGlobalBounds().contains(mousePos)) {
        // scroll event
    }

    if (mScrollBarClicked) {
        mScrollBarHasMoved = true;

        // Position all the way to bottom
        if (mousePos.y > mShapeRef->getPosition().y + mShapeRef->getSize().y -
            mScrollBarRef->getSize().y / 2) {

            float bottomScrollBarPosition = 0.0f;

            bottomScrollBarPosition += mShapeRef->getPosition().y;
            bottomScrollBarPosition += mShapeRef->getSize().y;
            bottomScrollBarPosition -= mScrollBarRef->getSize().y;

            mScrollBarRef->setPosition(Vect2f(mScrollBarRef->getPosition().x,
                                              bottomScrollBarPosition));

            setTextAutoScroll(true);

        } else if (mousePos.y < mShapeRef->getPosition().y +
                   mScrollBarRef->getSize().y / 2) {

            float topScrollBarPosition = mShapeRef->getPosition().y;
            mScrollBarRef->setPosition(Vect2f(mScrollBarRef->getPosition().x,
                                              topScrollBarPosition));

            mTextRef->setPosition(Vect2f(mTextRef->getPosition().x,
                                         mShapeRef->getPosition().y - mPadding));
        } else {
            mScrollBarRef->setPosition(
                        Vect2f(mScrollBarRef->getPosition().x,
                               mousePos.y - (mScrollBarRef->getSize().y / 2)));

            // Update the text postion
            float baseScrollPos = (mScrollBarRef->getPosition().y -
                                   mShapeRef->getPosition().y);

            float ratio         = mTextRef->getSize().y / mShapeRef->getSize().y;
            float basePosition  = baseScrollPos * ratio + (mPadding * 2);
            mTextRef->setPosition(
                        Vect2f(mTextRef->getPosition().x,
                               mShapeRef->getPosition().y - (basePosition)));
        }
    }

}

void TextListWidget::setScrollSpeed(float& scrollspeed) {
    mScrollSpeed = scrollspeed;
}

float TextListWidget::getScrollSpeed() {
    return mScrollSpeed;
}

void TextListWidget::setSize(const Vect2f& size) {
    mShapeRef->setSize(size);
    mSize = size;
}

Color TextListWidget::getColor() {
    return mShapeRef->getColor();
}

ColorGradient TextListWidget::getColorGradient() {
    return mShapeRef->getColorGradient();
}

bool TextListWidget::isColorGradient() {
    return mShapeRef->isColorGradient();
}

void TextListWidget::setColor(const Color& color) {
    mColor            = color;
    mHasColorGradient = false;
    mShapeRef->setColor(color);
}

void TextListWidget::setColor(const ColorGradient& color) {
    mColorGradient    = color;
    mHasColorGradient = true;
    mShapeRef->setColor(color);
}

void TextListWidget::setTextColor(const Color& color) {
    mTextColor = color;
    mTextRef->setColor(color);
}

Color TextListWidget::getTextColor() {
    return mTextColor;
}

void TextListWidget::setScrollBarColor(const Color& color) {
    mScrollBarRef->setColor(color);
    mScrollBarColor = color;
}

Color TextListWidget::getScrollBarColor() {
    return mScrollBarColor;
}

void TextListWidget::setTextAutoScroll(bool scroll) {
    mScrollBarAutoScroll = scroll;
}

bool TextListWidget::isTextAutoScroll() {
    return mScrollBarAutoScroll;
}

void TextListWidget::setExpandeSize(const Vect2f& size) {
    mMaxiumExpandSize = size;
}

Vect2f TextListWidget::getExpandSize() {
    return mMaxiumExpandSize;
}

void TextListWidget::setExpandVelocity(const float& velocity) {
    mExpandVelocity = velocity;
}

float TextListWidget::getExpandVelocity() {
    return mExpandVelocity;
}

bool TextListWidget::isExpanded() {
    return mIsExpanded;
}

// void TextListWidget::onClick(Event evt, Window& window) {
//     if (!isExpanded()) {
//         mEnableTransition = true;
//     } else {

//         Vect2i mousePos            = Mouse::getPosition(*window.getWindowPtr());
//         Vect2f mousePosWithPadding = Vect2f(mousePos.x + 3.f, mousePos.y + 3.f);
//         if (mShowScrollBar &&
//             mScrollBarRef->getGlobalBounds().contains(mousePosWithPadding)) {
//             mScrollBarClicked = true;
//         }
//     }
// }


void TextListWidget::setScale(const Vect2f& scale) {
    mShapeRef->setScale(scale);
    mTextRef->setScale(scale);
}

Vect2f TextListWidget::getScale() {
    return mShapeRef->getScale();
}

float TextListWidget::getRotation() {
    return mShapeRef->getRotation();
}

void TextListWidget::setRotation(const float& angle) {
    mShapeRef->setRotation(angle);
    mTextRef->setRotation(angle);
}

Vect2f TextListWidget::getOrigin() {
    return mShapeRef->getOrigin();
}

float TextListWidget::getOpacity() {
    return mShapeRef->getOpacity();
}

void TextListWidget::setOrigin(const Vect2f& origin) {
    mShapeRef->setOrigin(origin);
    // TODO(Pedro): Fix the text origin relative to the shape
}

void TextListWidget::setOpacity(const float& opacity) {
    mOpacity  = opacity;
    mTextRef->setOpacity(opacity);
    mShapeRef->setOpacity(opacity);
}

Area TextListWidget::getLocalBounds() {
    return mShapeRef->getLocalBounds();
}

Area TextListWidget::getGlobalBounds() {
    return mShapeRef->getGlobalBounds();
}

Vect2f TextListWidget::getSize() {
    return mShapeRef->getSize();
}

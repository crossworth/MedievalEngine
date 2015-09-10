#ifndef TEXTLISTWIDGET_H
#define TEXTLISTWIDGET_H
#include "GUI/Widget.h"

namespace ME {


class TextListWidget : public Widget {
public:
    TextListWidget();
    void init();
    void addText(const sf::String& text);
    void draw(Window& window);
    void update();
    void handleEvents(Event evt);
    void setScrollSpeed(float& scrollspeed);
    float getScrollSpeed();
    void setSize(const Vect2f& size);

    void setScale(const Vect2f& scale);
    Vect2f getScale();

    float getOpacity();

    float getRotation();
    void setRotation(const float& angle);

    Vect2f getOrigin();
    void setOrigin(const Vect2f& origin);


    void setColor(const Color& color);
    void setColor(const ColorGradient& color);
    Color getColor();
    ColorGradient getColorGradient();
    bool isColorGradient();

    void setTextColor(const Color& color);
    Color getTextColor();

    void setScrollBarColor(const Color& color);
    Color getScrollBarColor();

    void setTextAutoScroll(bool scroll);
    bool isTextAutoScroll();

    void setExpandeSize(const Vect2f& size);
    Vect2f getExpandSize();
    void setExpandVelocity(const float& velocity);
    float getExpandVelocity();

    bool isExpanded();

    void setOpacity(const float& opacity);

    Area getLocalBounds();
    Area getGlobalBounds();
    Vect2f getSize();
private:
    // Expande variables
    Vect2f mMaxiumExpandSize;
    bool mEnableTransition;
    bool mExpandTop;
    bool mIsExpanded;
    float mExpandVelocity;
    WindowInfo* winSize;

    // Scrollbar
    Shape* mScrollBarRef;
    Color mScrollBarColor;
    bool mShowScrollBar;
    bool mScrollBarClicked;
    bool mScrollBarHasMoved;
    bool mScrollBarAutoScroll;

    Vect2f mSize;
    Color mTextColor;
    float mPadding;
    float mScrollSpeed;
    float mLineHeight;
    sf::String mStringBuffer;
    Text* mTextRef;
    Shape* mShapeRef;
    Clock mClock;
};

}

#endif // TEXTLISTWIDGET_H

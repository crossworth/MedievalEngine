#ifndef TEXTSCROLLLISTOBJECT_H
#define TEXTSCROLLLISTOBJECT_H
#include "Helper/Clock.h"
#include "Events/Mouse.h"
#include "GUI/GUIObject.h"

namespace ME {

class TextScrollListObject : public GUIObject {
public:
    TextScrollListObject();
    void init();
    void addText(const std::wstring& text);
    void draw(Window& window);
    void update();
    void handleEvents(Event evt, Window& window);
    void setScrollSpeed(float& scrollspeed);
    float getScrollSpeed();
    void setSize(const Vect2f& size);
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

    void onClick(Event evt, Window& window);

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
    std::wstring mStringBuffer;
    Text* mTextRef;
    Shape* mShapeRef;
    Clock mClock;
};

}

#endif // TEXTSCROLLLISTOBJECT_H

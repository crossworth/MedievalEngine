#ifndef TEXTSCROLLLISTOBJECT_H
#define TEXTSCROLLLISTOBJECT_H
#include <GUI/GUIObject.h>

namespace ME {

class TextScrollListObject : public GUIObject {
public:
    TextScrollListObject();
    void addText(const std::wstring& text);
    void draw(Window& window);
    void update();
    void handleEvents(Event evt);
    void setSize(const Vect2f& size);
    void setBackgroundColor(const Color& color);
    void setBackgroundColor(const ColorGradient& color);
    void textColor(const Color& color);
    Color getTextColor();

    void onClick();

    void setOpacity(const float& opacity);

    Area getLocalBounds();
    Area getGlobalBounds();
    Vect2f getSize();
private:
    Vect2f mSize;
    Color mTextColor;
    float mPadding;
    float mScrollSpeed;
    float mLineHeight;
    std::wstring mStringBuffer;
    Text* mTextRef;
    Shape* mShapeRef;
};

}

#endif // TEXTSCROLLLISTOBJECT_H

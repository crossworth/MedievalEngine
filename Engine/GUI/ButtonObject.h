#ifndef BUTTONOBJECT_H
#define BUTTONOBJET_H
#include "Resources/ResourceManager.h"
#include "GUI/GUIObject.h"


namespace ME {

class ButtonObject : public GUIObject {
public:
    ButtonObject(const std::wstring& text,
                 Vect2f pos, ResourceID fontID = 0);
    void init();
    void draw(Window& window);
    void update();
    void handleEvents(Event evt, Window& window);

    void onMouseOver(Event evt, Window& window);
    void onMouseOut(Event evt, Window& window);

    void onClick(Event evt, Window& window);

    void setPosition(const Vect2f& pos);
    Vect2f getPosition();

    Vect2f getSize();

    void setOpacity(const float& opacity);
    float getOpacity();

    void setColor(const Color& color);
    Color getColor();
    void setColor(const ColorGradient& color);
    ColorGradient getColorGradient();
    bool isColorGradient();

    void setTextColor(const Color& color);
    Color getTextColor();

    Area getLocalBounds();
    Area getGlobalBounds();
private:
    ResourceID mShapeID;
    ResourceID mTextID;
    Text* mTextRef;
    Shape* mShapeRef;
    std::wstring mText;
    ResourceID mFontID;
};

}

#endif // BUTTONOBJET_H

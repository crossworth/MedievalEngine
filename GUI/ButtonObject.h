#ifndef BUTTONOBJECT_H
#define BUTTONOBJET_H
#include <Assets/AssetIDGenerator.h>
#include <Assets/AssetsManager.h>
#include <GUI/GUIObject.h>


namespace ME {

class ButtonObject : public GUIObject {
public:
    ButtonObject(const std::wstring& text,
                 Vect2f pos, AssetID fontID = 0);
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
    AssetID mShapeID;
    AssetID mTextID;
    Text* mTextRef;
    Shape* mShapeRef;
    std::wstring mText;
    AssetID mFontID;
};

}

#endif // BUTTONOBJET_H

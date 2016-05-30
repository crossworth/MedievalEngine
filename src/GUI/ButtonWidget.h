#ifndef BUTTONWIDGET_H
#define BUTTONWIDGET_H
#include "GUI/Widget.h"


namespace ME {

class ButtonWidget : public Widget {
public:
    ButtonWidget(const String& text,
                 Vect2f pos, ResourceID fontID = 0);
    void init();
    void draw(Window& window);
    void update();
    void handleEvents(Event evt);

    void setPosition(const Vect2f& pos);
    Vect2f getPosition();

    Vect2f getSize();

    void setSize(const Vect2f& size);
    void setScale(const Vect2f& scale);
    Vect2f getScale();

    void setOpacity(const float& opacity);
    float getOpacity();

    float getRotation();
    void setRotation(const float& angle);

    Vect2f getOrigin();
    void setOrigin(const Vect2f& origin);

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
    String mText;
    ResourceID mFontID;
};

}

#endif // BUTTONWIDGET_H

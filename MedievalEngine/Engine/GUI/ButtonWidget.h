#ifndef BUTTONWIDGET_H
#define BUTTONWIDGET_H
#include "Resources/ResourceManager.h"
#include "GUI/Widget.h"


namespace ME {

class ButtonWidget;

typedef std::shared_ptr<ButtonWidget> ButtonWidgetPtr;

class ButtonWidget : public Widget {
public:
    ButtonWidget(const sf::String& text,
                 Vect2f pos, ResourceID fontID = 0);
    void init();
    void draw(Window& window);
    void update();
    void handleEvents(Event evt);

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
    sf::String mText;
    ResourceID mFontID;
};

}

#endif // BUTTONWIDGET_H



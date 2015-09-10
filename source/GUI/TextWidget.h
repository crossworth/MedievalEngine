#ifndef TEXTWIDEGET_H
#define TEXTWIDEGET_H
#include "GUI/Widget.h"


namespace ME {


class TextWidget : public Widget {
public:
    TextWidget(const sf::String& text,
               const int& textSize,
               const Vect2f& pos = Vect2f(), const ResourceID& fontID = 0);

    void setFont(const ResourceID& fontID);
    ResourceID getFont();

    void init();
    void draw(Window& window, sf::RenderStates* state);
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

    Area getLocalBounds();
    Area getGlobalBounds();
private:
    ResourceID mFontID;
    ResourceID mTextID;
    Text* mTextRef;
    sf::String mText;
    int mTextSize;

    bool mIsMouseOver;
};

}

#endif // TEXTWIDEGET_H

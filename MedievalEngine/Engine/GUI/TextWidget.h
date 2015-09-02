#ifndef TEXTWIDEGET_H
#define TEXTWIDEGET_H
#include "Resources/ResourceManager.h"
#include "GUI/Widget.h"


namespace ME {

class TextWidget;

typedef std::shared_ptr<TextWidget> TextWidgetPtr;

class TextWidget : public Widget {
public:
    TextWidget(const sf::String& text,
               const int& textSize,
               const Vect2f& pos = Vect2f(), const ResourceID& fontID = 0);

    void setFont(const ResourceID& fontID);
    ResourceID getFont();

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

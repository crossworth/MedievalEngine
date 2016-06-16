#ifndef MEDIEVALENGINE_RESOURCES_TEXT_H_
#define MEDIEVALENGINE_RESOURCES_TEXT_H_
#include "Resources/Font.h"
#include "Effects/Effect.h"


namespace ME {

class Text : public Resource, public Drawable {
public:
    enum class FontStyle : char {
        REGULAR, 
        BOLD, 
        ITALIC, 
        UNDERLINE
    };
    
    Text();

    sf::Text* getResourcePointer();

    void setFont(Font &font);
    void setFontSize(const unsigned int &size);
    void setString(const String &text);
    void setStyle(const Text::FontStyle&  tyle);

    void setTextShadow(const float &factor = 2.0f,
                       const Color &color = Color::BLACK);


    float getFontHeight(const unsigned int &size);


    void removeTextShadow();
    bool isTextShadowEnable();

    String getString();
    unsigned int getFontSize();
    Text::FontStyle getStyle();


    void draw(Window& window);

    void setPosition(const Vect2f &pos);
    Vect2f getPosition();
    void move(const Vect2f &pos);

    void setSize(const Vect2f &size);
    Vect2f getSize();
    void setScale(const Vect2f &scale);
    Vect2f getScale();

    void setColor(const Color &color);
    Color getColor();

    float getRotation();
    void setRotation(const float &angle);
    void rotate(const float &angle);

    Vect2f getOrigin();
    void setOrigin(const Vect2f &origin);

    Area getLocalBounds();
    Area getGlobalBounds();
private:
    Color mTextShadow;
    float mTextShadowFactor;
    bool mHasTextShadow;
    sf::Text mText;
};

}

#endif // MEDIEVALENGINE_RESOURCES_TEXT_H_

#ifndef TEXT_H
#define TEXT_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Graphics/Drawable.h>
#include <Assets/Asset.h>
#include <Assets/Font.h>
#include <Effects/Effects.h>


namespace ME {

enum FONT_STYLE {REGULAR, BOLD, ITALIC, UNDERLINE};

class Text : public Asset, public Drawable {
public:
    Text();

    sf::Text* getResourcePointer();

    void setFont(Font& font);
    void setFontSize(const unsigned int& size);
    void setString(const std::wstring& text);
    void setStyle(const FONT_STYLE& style);

    void setTextShadow(const float& factor = 2.0f, const Color& color = Color::BLACK);
    void removeTextShadow();
    bool isTextShadowEnable();

    std::string getString();
    unsigned int getFontSize();
    FONT_STYLE getStyle();

    void draw(sf::RenderWindow* renderWindow);

    void setPosition(const Vect2f& pos);
    Vect2f getPosition();
    void move(const Vect2f& pos);

    void setSize(const Vect2f& size);
    Vect2f getSize();
    void setScale(const Vect2f& scale);
    Vect2f getScale();

    void setColor(const Color& color);
    Color getColor();

    float getRotation();
    void setRotation(const float& angle);
    void rotate(const float& angle);

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

#endif // TEXT_H

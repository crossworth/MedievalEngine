#ifndef TEXT_H
#define TEXT_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Assets/Asset.h>
#include <Graphics/Drawable.h>
#include <Assets/Font.h>

namespace ME {

enum FONT_STYLE {REGULAR, BOLD, ITALIC, UNDERLINE};

class Text : public Asset, public Drawable {
public:
    Text();

    sf::Text* getResourcePointer();

    void setFont(Font &font);
    void setFontSize(const unsigned int &size);
    void setString(const std::string &text);
    void setStyle(const FONT_STYLE &style);

    void setTextShadow(const float &factor = 2.0f, const Color &color = Color::BLACK);
    void removeTextShadow();

    std::string getString();
    unsigned int getFontSize();
    FONT_STYLE getStyle();

    void draw(sf::RenderWindow *renderWindow);

    void setPosition(const Vect2f &pos);
    Vect2f getPosition();

    void setSize(const Vect2f &size);
    Vect2f getSize();

    void setColor(const Color &color);
    Color getColor();

private:
    Color mTextShadow;
    float mTextShadowFactor;
    bool _hasTextShadow;
    sf::Text mText;
};

}

#endif // TEXT_H

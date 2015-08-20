#ifndef SHAPE_H
#define SHAPE_H
#include <Assets/Asset.h>
#include <Graphics/Drawable.h>

namespace ME {

class Shape : public Asset, public Drawable {
public:
    Shape(const Vect2f &size, const Color &color, const Vect2f &pos);

    void draw(sf::RenderWindow *renderWindow);

    void setPosition(const Vect2f &pos);
    Vect2f getPosition();
    void move(const Vect2f &pos);

    void setSize(const Vect2f &size);
    Vect2f getSize();

    void setScale(const Vect2f &scale);
    Vect2f getScale();

    void setColor(const Color &color);
    Color getColor();

    void setBorderColor(const Color &color);
    Color getBorderColor();

    void setBorderSize(const float &size);
    float getBorderSize();

    float getRotation();
    void setRotation(const float &angle);
    void rotate(const float &angle);

    Vect2f getOrigin();
    void setOrigin(const Vect2f &origin);

    Area getLocalBounds();
    Area getGlobalBounds();

private:
    sf::RectangleShape mShape;
};

}

#endif // SHAPE_H

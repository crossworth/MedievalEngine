#ifndef MEDIEVALENGINE_RESOURCES_SHAPE_H_
#define MEDIEVALENGINE_RESOURCES_SHAPE_H_

#include "Helper/Math.h"

#include "Resources/Resource.h"

#include "Effects/Effect.h"

namespace ME {

class Shape : public Resource, public Drawable {
public:
    Shape(const Vect2f &size, const Color &color, const Vect2f &pos);

    void draw(Window &window);

    sf::RectangleShape* getResourcePointer();

    void setPosition(const Vect2f &pos);
    Vect2f getPosition();
    void move(const Vect2f &pos);

    void setSize(const Vect2f &size);
    Vect2f getSize();

    void setScale(const Vect2f &scale);
    Vect2f getScale();

    void setColor(const Color &color);
    Color getColor();

    void setColor(const ColorGradient &color);
    ColorGradient getColorGradient();

    bool isColorGradient();

    void setRadius(const float &radius);
    float getRadius();

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
    bool mIsGradientColor;
    uint32 mNumberPoints;
    float mRadius;
    ColorGradient mGradientColor;
    sf::RectangleShape mShape;
};

}

#endif // MEDIEVALENGINE_RESOURCES_SHAPE_H_

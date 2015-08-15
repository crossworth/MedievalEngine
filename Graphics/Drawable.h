#ifndef DRAWABLE_H
#define DRAWABLE_H
#include <Helper/Vect2.h>
#include <SFML/Graphics.hpp>
#include <Helper/Color.h>

namespace ME {

class Drawable {
public:
    Drawable();

    virtual sf::Drawable* getObject() = 0;

    virtual void setPosition(const Vect2f &pos) = 0;
    virtual Vect2f getPosition() = 0;

    virtual void setSize(const Vect2f &size) = 0;
    virtual Vect2f getSize() = 0;

    virtual void setColor(const Color &color) = 0;
    virtual Color getColor() = 0;

protected:


};

}

#endif // DRAWABLE_H

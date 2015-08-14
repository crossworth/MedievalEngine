#ifndef DRAWABLE_H
#define DRAWABLE_H
#include <Headers.h>

namespace ME {

class Drawable {
public:
    Drawable();

    virtual sf::Drawable* getObject() = 0;

    virtual void setPosition(const Vect2f &pos) = 0;
    virtual Vect2f getPosition() = 0;

    virtual void setSize(const Vect2f &size) = 0;
    virtual Vect2f getSize() = 0;

    virtual void setColor(const ME::Color &color) = 0;
    virtual ME::Color getColor() = 0;

protected:


};

}

#endif // DRAWABLE_H

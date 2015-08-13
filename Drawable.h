#ifndef DRAWABLE_H
#define DRAWABLE_H
#include "Config.h"

namespace ME {

class Drawable {
public:
    Drawable();

    virtual void draw() = 0;

    virtual void setPosition(const Coord &pos) = 0;
    virtual Coord getPosition() = 0;

    virtual void setSize(const Coord &size) = 0;
    virtual Coord getSize() = 0;

    virtual void setColor(const Color &color) = 0;
    virtual Color getColor() = 0;

protected:


};

}

#endif // DRAWABLE_H

#ifndef COLORGRADIENT_H
#define COLORGRADIENT_H
#include <Helper/Color.h>


namespace ME {

class ColorGradient {
public:
    ColorGradient();
    ColorGradient(const Color& top, const Color& bottom);
    ColorGradient& operator=(const ColorGradient& other);
    Color top;
    Color bottom;
};

}

#endif // COLORGRADIENT_H

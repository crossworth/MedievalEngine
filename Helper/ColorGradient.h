#ifndef COLORGRADIENT_H
#define COLORGRADIENT_H
#include <Helper/Color.h>

namespace ME {

class ColorGradient {
public:
    ColorGradient();
    ColorGradient(const Color& color1, const Color& color2);
    ColorGradient& operator=(const ColorGradient& other);
    Color color1;
    Color color2;
};

}

#endif // COLORGRADIENT_H

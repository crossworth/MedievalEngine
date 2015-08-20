#ifndef GRADIENTCOLOR_H
#define GRADIENTCOLOR_H
#include <Helper/Color.h>

namespace ME {

class GradientColor {
public:
    GradientColor();
    GradientColor(const Color& color1, const Color& color2);
    GradientColor& operator=(const GradientColor& other);
    Color color1;
    Color color2;
};

}

#endif // GRADIENTCOLOR_H

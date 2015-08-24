#include "ColorGradient.h"

using namespace ME;

ColorGradient::ColorGradient() : top(Color::WHITE), bottom(Color::BLACK) {

}

ColorGradient::ColorGradient(const Color& color1, const Color& color2) {
    this->top = color1;
    this->bottom = color2;
}

ColorGradient& ColorGradient::operator=(const ColorGradient& other) {
    top = other.top;
    bottom = other.bottom;

    return *this;
}

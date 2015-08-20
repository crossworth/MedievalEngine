#include "ColorGradient.h"

using namespace ME;

ColorGradient::ColorGradient() : color1(Color::WHITE), color2(Color::BLACK) {

}

ColorGradient::ColorGradient(const Color& color1, const Color& color2) {
    this->color1 = color1;
    this->color2 = color2;
}

ColorGradient& ColorGradient::operator=(const ColorGradient& other) {
    color1 = other.color1;
    color2 = other.color2;

    return *this;
}

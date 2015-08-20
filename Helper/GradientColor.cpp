#include "GradientColor.h"

using namespace ME;

GradientColor::GradientColor() : color1(Color::WHITE), color2(Color::BLACK) {

}

GradientColor::GradientColor(const Color &color1, const Color &color2) {
    this->color1 = color1;
    this->color2 = color2;
}

GradientColor& GradientColor::operator=(const GradientColor& other) {
    color1 = other.color1;
    color2 = other.color2;

    return *this;
}

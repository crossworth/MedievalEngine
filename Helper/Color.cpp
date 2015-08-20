#include "Color.h"

using namespace ME;

Color::Color() {
    red   = 255;
    green = 255;
    blue  = 255;
    alpha = 255;
}

Color::Color(const Color& other) {
    red   = other.red;
    green = other.green;
    blue  = other.blue;
    alpha = other.alpha;
}

Color::Color(const COLORS &color) {
    switch (color) {
    case WHITE:
        red   = 255;
        green = 255;
        blue  = 255;
        alpha = 255;
        break;
    case BLACK:
        red   = 0;
        green = 0;
        blue  = 0;
        alpha = 255;
        break;
    case RED:
        red   = 255;
        green = 0;
        blue  = 0;
        alpha = 255;
        break;
    case GREEN:
        red   = 0;
        green = 255;
        blue  = 0;
        alpha = 255;
        break;
    case BLUE:
        red   = 0;
        green = 0;
        blue  = 255;
        alpha = 255;
        break;
    case BUTTON_C1:
        red   = 235;
        green = 235;
        blue  = 235;
        alpha = 255;
        break;
    case BUTTON_C2:
        red   = 246;
        green = 246;
        blue  = 246;
        alpha = 255;
        break;
    case BUTTON_C3:
        red   = 208;
        green = 208;
        blue  = 210;
        alpha = 255;
        break;
    default:
        break;
    }
}

Color::Color(const int &red, const int &green, const int &blue, const int &alpha) {
    this->red   = red;
    this->blue  = blue;
    this->green = green;
    this->alpha = alpha;
}

Color& Color::operator=(const Color& other) {
    red   = other.red;
    green = other.green;
    blue  = other.blue;
    alpha = other.alpha;

    return *this;
}


#include "Color.h"

using namespace ME;

Color::Color() {
    red   = 255;
    green = 255;
    blue  = 255;
    alpha = 255;
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



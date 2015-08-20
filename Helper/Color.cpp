#include "Color.h"

using namespace ME;

Color Color::BUTTON_C1(235, 235, 235);
Color Color::BUTTON_C2(246, 246, 246);
Color Color::BUTTON_C3(208, 208, 210);

Color Color::WHITE(255, 255, 255);
Color Color::BLACK(0, 0, 0);


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

Color::Color(const int &red, const int &green, const int &blue, const int &alpha) {
    this->red   = red;
    this->blue  = blue;
    this->green = green;
    this->alpha = alpha;
}



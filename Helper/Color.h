#ifndef COLOR_H
#define COLOR_H

namespace ME {

class Color {
public:
    Color();
    inline Color& operator=(const Color& other);
    inline bool operator==(const Color& color);
    inline bool operator!=(const Color& color);
    Color(const Color& other);
    Color(const int& red, const int& green, const int& blue, const int& alpha = 255);

    int red;
    int green;
    int blue;
    int alpha;

public:
    static Color BUTTON_C1;
    static Color BUTTON_C2;
    static Color BUTTON_C3;

    static Color WHITE;
    static Color BLACK;
//    static Color RED;
//    static Color LIME;
//    static Color BLUE;
//    static Color YELLOW;
//    static Color CYAN;
//    static Color MAGENTA;
//    static Color SILVER;
//    static Color GRAY;
//    static Color MAROON;
//    static Color OLIVE;
//    static Color GREEN;
//    static Color PURPLE;
//    static Color TEAL;
//    static Color NAVY;
};

Color& Color::operator=(const Color& other) {
    red   = other.red;
    green = other.green;
    blue  = other.blue;
    alpha = other.alpha;

    return *this;
}

inline bool Color::operator==(const Color& color) {
    return (red == color.red && green == color.green && blue == color.blue && alpha == color.alpha);
}

inline bool Color::operator!=(const Color& color) {
    return !(*this == color);
}




}

#endif // COLOR_H

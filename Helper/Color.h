#ifndef COLOR_H
#define COLOR_H

namespace ME {

class Color {
public:
    enum COLORS { WHITE, BLACK, RED, BLUE, GREEN };
public:
    Color();
    Color(const Color& other);
    Color(const COLORS &color);
    Color(const int &red, const int &green, const int &blue, const int &alpha = 255);

    int red;
    int green;
    int blue;
    int alpha;
};

}

#endif // COLOR_H

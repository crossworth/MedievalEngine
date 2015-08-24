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
    Color(const int& red, const int& green,
          const int& blue, const int& alpha = 255);

    int red;
    int green;
    int blue;
    int alpha;

public:
    static Color BUTTON_C1;
    static Color BUTTON_C2;
    static Color BUTTON_C3;

    static Color WHITE;
    static Color LIME;
    static Color BLUE;
    static Color YELLOW;
    static Color CYAN;
    static Color MAGENTA;
    static Color SILVER;
    static Color GRAY;
    static Color MAROON;
    static Color GREEN;
    static Color PURPLE;
    static Color TEAL;
    static Color NAVY;
    static Color DARK_RED;
    static Color BROWN;
    static Color FIREBRICK;
    static Color CRIMSON;
    static Color RED;
    static Color TOMATO;
    static Color CORAL;
    static Color INDIAN_RED;
    static Color LIGHT_CORAL;
    static Color DARK_SALMON;
    static Color SALMON;
    static Color LIGHT_SALMON;
    static Color ORANGE_RED;
    static Color DARK_ORANGE;
    static Color ORANGE;
    static Color GOLD;
    static Color DARK_GOLDEN_ROD;
    static Color GOLDEN_ROD;
    static Color PALE_GOLDEN_ROD;
    static Color DARK_KHAKI;
    static Color KHAKI;
    static Color OLIVE;
    static Color YELLOW_GREEN;
    static Color DARK_OLIVE_GREEN;
    static Color OLIVE_DRAB;
    static Color LAWN_GREEN;
    static Color CHART_REUSE;
    static Color GREEN_YELLOW;
    static Color DARK_GREEN;
    static Color FOREST_GREEN;
    static Color LIME_GREEN;
    static Color LIGHT_GREEN;
    static Color PALE_GREEN;
    static Color DARK_SEA_GREEN;
    static Color MEDIUM_SPRING_GREEN;
    static Color SPRING_GREEN;
    static Color SEA_GREEN;
    static Color MEDIUM_AQUA_MARINE;
    static Color MEDIUM_SEA_GREEN;
    static Color LIGHT_SEA_GREEN;
    static Color DARK_SLATE_GRAY;
    static Color DARK_CYAN;
    static Color AQUA;
    static Color LIGHT_CYAN;
    static Color DARK_TURQUOISE;
    static Color TURQUOISE;
    static Color MEDIUM_TURQUOISE;
    static Color PALE_TURQUOISE;
    static Color AQUA_MARINE;
    static Color POWDER_BLUE;
    static Color CADET_BLUE;
    static Color STEEL_BLUE;
    static Color CORN_FLOWER_BLUE;
    static Color DEEP_SKY_BLUE;
    static Color DODGER_BLUE;
    static Color LIGHT_BLUE;
    static Color SKY_BLUE;
    static Color LIGHT_SKY_BLUE;
    static Color MIDNIGHT_BLUE;
    static Color DARK_BLUE;
    static Color MEDIUM_BLUE;
    static Color ROYAL_BLUE;
    static Color BLUE_VIOLET;
    static Color INDIGO;
    static Color DARK_SLATE_BLUE;
    static Color SLATE_BLUE;
    static Color MEDIUM_SLATE_BLUE;
    static Color MEDIUM_PURPLE;
    static Color DARK_MAGENTA;
    static Color DARK_VIOLET;
    static Color DARK_ORCHID;
    static Color MEDIUM_ORCHID;
    static Color THISTLE;
    static Color PLUM;
    static Color VIOLET;
    static Color ORCHID;
    static Color MEDIUM_VIOLET_RED;
    static Color PALE_VIOLET_RED;
    static Color DEEP_PINK;
    static Color HOT_PINK;
    static Color LIGHT_PINK;
    static Color PINK;
    static Color ANTIQUE_WHITE;
    static Color BEIGE;
    static Color BISQUE;
    static Color BLANCHED_ALMOND;
    static Color WHEAT;
    static Color CORN_SILK;
    static Color LEMON_CHIFFON;
    static Color LIGHT_GOLDEN_ROD_YELLOW;
    static Color LIGHT_YELLOW;
    static Color SADDLE_BROWN;
    static Color SIENNA;
    static Color CHOCOLATE;
    static Color PERU;
    static Color SANDY_BROWN;
    static Color BURLY_WOOD;
    static Color TAN;
    static Color ROSY_BROWN;
    static Color MOCCASIN;
    static Color NAVAJO_WHITE;
    static Color PEACH_PUFF;
    static Color MISTY_ROSE;
    static Color LAVENDER_BLUSH;
    static Color LINEN;
    static Color OLD_LACE;
    static Color PAPAYA_WHIP;
    static Color SEA_SHELL;
    static Color MINT_CREAM;
    static Color SLATE_GRAY;
    static Color LIGHT_SLATE_GRAY;
    static Color LIGHT_STEEL_BLUE;
    static Color LAVENDER;
    static Color FLORAL_WHITE;
    static Color ALICE_BLUE;
    static Color GHOST_WHITE;
    static Color HONEYDEW;
    static Color IVORY;
    static Color AZURE;
    static Color SNOW;
    static Color BLACK;
    static Color DIM_GRAY;
    static Color DARK_GRAY;
    static Color LIGHT_GRAY;
    static Color GAINSBORO;
    static Color WHITE_SMOKE;
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

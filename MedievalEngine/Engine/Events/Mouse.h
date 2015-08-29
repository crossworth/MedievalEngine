#ifndef MOUSE_H
#define MOUSE_H
#include <SFML/Window/Mouse.hpp>
#include "Helper/Vect2.h"


namespace ME {

class Mouse {
public:

    enum Button {
        Left,       ///< The left mouse button
        Right,      ///< The right mouse button
        Middle,     ///< The middle (wheel) mouse button
        XButton1,   ///< The first extra mouse button
        XButton2,   ///< The second extra mouse button

        ButtonCount ///< Keep last -- the total number of mouse buttons
    };

    enum Wheel {
        VerticalWheel,  ///< The vertical mouse wheel
        HorizontalWheel ///< The horizontal mouse wheel
    };

    static bool isButtonPressed(Mouse::Button button);
    static Vect2i getPosition();
    static Vect2i getPosition(sf::Window& window);
    static void setPosition(const Vect2i& position);
};

}
#endif // MOUSE_H

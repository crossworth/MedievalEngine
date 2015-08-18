#ifndef EVENTS_H
#define EVENTS_H
#include <SFML/Graphics.hpp>
#include <Events/Keyboard.h>
#include <Events/Mouse.h>

namespace ME {

class Events {
public:
    Events();

    struct SizeEvent {
        uint width;
        uint height;
    };

    struct TextEvent {
        uint32_t unicode;
    };

    struct KeyEvent {
        Keyboard::KEY code;
        bool          alt;
        bool          control;
        bool          shift;
        bool          system;
    };

    struct MouseMoveEvent {
        int x;
        int y;
    };

    struct MouseButtonEvent {

    };

};

}

#endif // EVENTS_H

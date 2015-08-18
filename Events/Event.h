#ifndef EVENT_H
#define EVENT_H
#include <SFML/Graphics.hpp>
#include <Events/Keyboard.h>
#include <Events/Mouse.h>

namespace ME {

class Event {
public:
    struct SizeEvent {
        unsigned int width;
        unsigned int height;
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
        Mouse::Button button;
        int           x;
        int           y;
    };

    struct MouseWheelEvent {
        int delta;
        int x;
        int y;
    };

    struct MouseWheelScrollEvent {
        Mouse::Wheel wheel;
        float        delta;
        int          x;
        int          y;
    };

    enum EventType {
        Closed,
        Resized,
        LostFocus,
        GainedFocus,
        TextEntered,
        KeyPressed,
        KeyReleased,
        MouseWheelMoved,
        MouseWheelScrolled,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseEntered,
        MouseLeft,

        Count
    };

    EventType type;

    union {
        SizeEvent             size;
        KeyEvent              key;
        TextEvent             text;
        MouseMoveEvent        mouseMove;
        MouseButtonEvent      mouseButton;
        MouseWheelEvent       mouseWheel;
        MouseWheelScrollEvent mouseWheelScroll;
    };
};

}

#endif // EVENTS_H

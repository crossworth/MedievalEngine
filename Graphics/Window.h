#ifndef WINDOW_H
#define WINDOW_H
#include <Headers.h>
#include <SFML/Graphics.hpp>

namespace ME {

class Window {
public:
    Window();
    void create();
    void close();
    bool isOpen();
    bool pollEvent(sf::Event &event);
    Vect2i getPosition();
    void setPosition(const Vect2i &pos);
    Vect2i getSize();
    void setSize(const Vect2i &size);

    void setTile(const std::string &title);
    void setIcon(unsigned int width, unsigned int height, const sf::Uint8 *pixels);

    void setVisible(const bool &visible);

    void display();
};

}

#endif // WINDOW_H

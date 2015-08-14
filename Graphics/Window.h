#ifndef WINDOW_H
#define WINDOW_H
#include <Headers.h>
#include <SFML/Graphics.hpp>

namespace ME {

class Window {
public:
    Window();
    void create(const WindowInfo &info);
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

    void clear();
    void draw(Drawable &obj);
    void display();

    ~Window();
protected:
    bool isValidWindow(const WindowInfo &info);

private:
    sf::RenderWindow *mWindow;
    WindowInfo mWindowInfo;
};

}

#endif // WINDOW_H

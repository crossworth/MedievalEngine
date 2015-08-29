#ifndef WINDOW_H
#define WINDOW_H
#include <SFML/Graphics.hpp>
#include "Events/Event.h"
#include "Graphics/WindowInfo.h"
#include "Graphics/Drawable.h"
#include "Helper/Vect2.h"


namespace ME {

class Window {
public:
    Window();
    void create(const WindowInfo &info);
    void close();
    bool isOpen();
    bool pollEvent(Event &evt);
    Vect2i getPosition();
    void setPosition(const Vect2i &pos);
    Vect2i getSize();
    void setSize(const Vect2i &size);

    void setTile(const std::string &title);
    void setIcon(const std::string &fileName);

    void setVisible(const bool &visible);

    void clear();
    void draw(Drawable *obj);
    void display();

    sf::RenderWindow* getWindowPtr();

    WindowInfo* getWindowInfo();

    ~Window();
protected:
    bool isValidWindow(const WindowInfo &info);

private:
    sf::RenderWindow *mWindow;
    WindowInfo mWindowInfo;
};

}

#endif // WINDOW_H

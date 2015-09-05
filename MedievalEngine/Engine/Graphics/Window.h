#ifndef WINDOW_H
#define WINDOW_H
#include <memory>
#include <SFML/Graphics.hpp>
#include "Events/Event.h"
#include "Graphics/WindowInfo.h"
#include "Graphics/Drawable.h"
#include "Helper/Vect2.h"
#include "Helper/Clock.h"


namespace ME {

class Widget;
typedef std::shared_ptr<Widget> WidgetPtr;


class Window {
public:
    enum Position {Left, Right, Center, Top, Bottom};
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


    static void fullScreen(Drawable* object);
    static void setRelative(Drawable* object);

    static void setPosition(Drawable* object,
                            const Window::Position& posX,
                            const Window::Position& posY,
                            Drawable* reference = nullptr
                        );
    static void setPosition(WidgetPtr object,
                            const Window::Position& posX,
                            const Window::Position& posY,
                            Drawable* reference = nullptr
                        );

    static int fontSize(const float& size);


    sf::RenderWindow* getWindowPtr();
    unsigned int getDelta();

    WindowInfo* getWindowInfo();

    ~Window();
protected:
    bool isValidWindow(const WindowInfo &info);

private:
    sf::RenderWindow *mWindow;
    static WindowInfo mWindowInfo;
    Clock mClock;
};

}

#endif // WINDOW_H

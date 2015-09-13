#ifndef WINDOW_H
#define WINDOW_H
#include "Events/Event.h"
#include "Graphics/WindowInfo.h"
#include "Graphics/Drawable.h"
#include "Helper/Clock.h"
#include "Lua/LuaAPI.h"


namespace ME {


class Window {
public:
    enum Position {LEFT, RIGHT, CENTER, TOP, BOTTOM};
public:
    Window();
    void create(const WindowInfo &info);
    void open();
    void close();
    bool isOpen();
    bool pollEvent(Event &evt);
    Vect2i getPosition();
    void setPosition(const Vect2i &pos);
    Vect2i getSize();
    void setSize(const Vect2i &size);

    void setTitle(const std::string &title);
    void setIcon(const std::string &fileName);

    void setVisible(const bool &visible);

    void clear();
    void draw(Drawable *obj);
    void display();

    void setCursorVisible(const bool& visible);

    static void setSizeFullScreen(Drawable* object);
    // TODO(Pedro): rename this function to something more
    // easy to understand like setSizeRelative
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

    void setCursor(const std::string& cursor);
    bool hasCustomCursor();

    sf::RenderWindow* getWindowPtr();
    
    unsigned int getDelta();
    inline unsigned int getFPS() {
        return getDelta();
    }

    unsigned int getDrawCalls();

    WindowInfo* getWindowInfo();

    ~Window();
protected:
    bool mIsWindowOpen;
    bool isValidWindow(const WindowInfo& info);
private:
    unsigned int mDrawCalls;
    unsigned int mFPS;
    unsigned int mFrame;
    sf::Sprite mCursor;
    sf::View mFixedView;
    bool mHasCustomCursor;
    bool mCursorVisible;
    sf::Texture mCursorTexture;

    sf::RenderWindow *mWindow;
    static WindowInfo mWindowInfo;
    Clock mClock;
};

}

#endif // WINDOW_H

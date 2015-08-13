#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H
#include "TO.h"
#include "Log.h"
#include "Profiler.h"
#include "Config.h"

namespace ME {

class RenderWindow {
public:
    static RenderWindow* getInstance();
    void createWindow(const windowInformation winInfos, int frameLimit = ENGINE_DEFAULTS::FRAME_LIMIT, bool vysnc = ENGINE_DEFAULTS::VSYNC);
    void clear(const sf::Color &color = sf::Color(0,0,0,255));
    bool isOpen();
    void display();
    void close();
    void setIcon(int width, int height, Image icon);
    bool pollEvent(Event &evt);
    void draw(const sf::Drawable &draw);
    Camera *createCamera(const std::string &name, const FloatRect &rect);
    Camera *createCamera(const std::string &name, const Camera &cam);
    Camera *getCamera(const std::string &name);
    Camera *getDefaultCamera();
    void setCamera(const std::string &name);
    void setCamera(const Camera &cam);
    bool isValidWindow(const windowInformation winInfos);
    windowInformation getWindowInformation();
    sf::RenderWindow *getRenderWindow();
    Coord getCameraPosition(const std::string &name);

    float getTime();
    void restartTime();

    ~RenderWindow();

    bool hasFocus;
private:
    Debugger *dbg;
    RenderWindow();
    static RenderWindow* instance;
    windowInformation mWindowInfomation;
    RenderWindow(const windowInformation rederInfo);
    sf::RenderWindow *Window;
    std::map<std::string, Camera*> mCameras;
    sf::Clock mClock;
};

}

#endif // RENDERWINDOW_H

#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H
#include "converter.h"
#include "debugger.h"
#include "profiler.h"
#include "engine_config.h"

namespace ME{

class renderWindow
{
public:
    static renderWindow* getInstance();
    void createWindow(const windowInformation winInfos,int frameLimit = 60, bool Sync = true);
    void clear(const sf::Color &c = sf::Color(0,0,0,255));
    bool isOpen();
    void display();
    void close();
    bool pollEvent(Event &evt);
    void draw(const sf::Drawable &draw);
    Camera *createCamera(const std::string &name, const FloatRect &rect);
    Camera *createCamera(const std::string &name, const Camera &cam);
    Camera *getCamera(const std::string &name);
    Camera *getDefaultCamera();
    void setCamera(const std::string &name);
    void setCamera(const Camera &cam);
    ~renderWindow();
     bool isValidWindow(const windowInformation winInfos);
     windowInformation getWindowInformation();
     sf::RenderWindow *getRenderWindow();
     Coord getCameraPosition(const std::string &name);
private:
    Debugger *dbg;
    renderWindow();
    windowInformation mWindowInfomation;
    renderWindow(const windowInformation rederInfo);
    sf::RenderWindow *Window;
    std::map<std::string,Camera*> mCameras;
};

}

#endif // RENDERWINDOW_H

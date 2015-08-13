#ifndef GUIOBJECT_H
#define GUIOBJECT_H
#include "Config.h"
#include "RenderWindow.h"
#include "Log.h"
#include "AssetsManager.h"

namespace ME {

class GUIObject {
public:
    GUIObject();

    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void processEvents(Event evt) = 0;

    virtual void show();
    virtual void hide();

    virtual void setPosition(const Coord &pos);
    Coord getPosition();

    virtual void setOpacity(const float &opacity);
    float getOpacity();

    virtual void setColor(const sf::Color &color);
    sf::Color getColor();

    bool isVisible();
    bool isActive();

protected:
    bool _isVisible;
    bool _isActive;
    Coord mPos;
    float mOpacity;
    sf::Color mColor;

    Debugger* dbg;
    AssetsManager* assets;
    RenderWindow* renderWindow;
};

}

#endif // GUIOBJECT_H

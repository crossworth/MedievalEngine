#ifndef WIDGET_H
#define WIDGET_H
#include <list>
#include <memory>
#include <algorithm>
#include "LogInc.h"
#include "Resources/ResourceManager.h"
#include "Graphics/Drawable.h"
#include "Graphics/Window.h"
#include "Events/Event.h"
#include "GUI/GUIEvent.h"

namespace ME {


class Widget;

typedef std::shared_ptr<Widget> WidgetPtr;

class Widget {
public:
    Widget();
    void registerWindow(Window* window);
    void registerResourceManager(ResourceManager* resource);

    virtual void init() = 0;
    virtual void draw(Window& window) = 0;
    virtual void update() = 0;
    virtual void handleEvents(Event evt) = 0;

    virtual void show();
    virtual void hide();

    virtual void setPosition(const Vect2f& pos);
    virtual Vect2f getPosition();
    virtual Vect2f getSize() = 0;

    virtual void setOpacity(const float& opacity);
    virtual float getOpacity();

    virtual void setColor(const Color& color);
    virtual Color getColor();

    virtual Area getLocalBounds() = 0;
    virtual Area getGlobalBounds() = 0;

    bool isVisible();
    bool isActive();
    bool isColorGradient();

    virtual void setEnable(bool active);

    std::string getType();

    void addEventHandle(GUIEventPtr event);
    void removeEventHandle(GUIEventPtr event);

    Window* getWindow();
    ResourceManager* getResourceManager();
protected:
    void notify(GUIEvent::Type type, Widget* widget);

    std::string mType;

    std::list<GUIEventPtr> mEvents;

    bool mIsVisible;
    bool mIsActive;
    bool mHasColorGradient;
    float mOpacity;
    Vect2f mPos;
    Color mColor;
    ColorGradient mColorGradient;

    Window* mWindow;
    ResourceManager* mResources;
    ResourceID mDefaultFontID;
};

}

#endif // WIDGET_H

#ifndef GUIOBJECT_H
#define GUIOBJECT_H
#include <Graphics/Drawable.h>
#include <Graphics/Window.h>
#include <Events/Event.h>
#include <LogInc.h>

namespace ME {

class GUIObject {
public:
    GUIObject();

    virtual void draw(Window &window) = 0;
    virtual void update() = 0;
    virtual void handleEvents(Event evt) = 0;

    virtual void show();
    virtual void hide();

    virtual void onMouseOver();
    virtual void onMouseOut();

    virtual void onClick();

    virtual void setPosition(const Vect2f &pos);
    virtual Vect2f getPosition();

    virtual Vect2f getSize() = 0;

    virtual void setOpacity(const float &opacity);
    virtual float getOpacity();

    virtual void setColor(const Color &color);
    virtual Color getColor();

    virtual Area getLocalBounds() = 0;
    virtual Area getGlobalBounds() = 0;

    bool isVisible();
    bool isActive();

protected:
    bool _isVisible;
    bool _isActive;
    Vect2f mPos;
    float mOpacity;
    Color mColor;
};

}

#endif // GUIOBJECT_H

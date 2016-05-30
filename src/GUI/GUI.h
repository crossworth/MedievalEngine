#ifndef GUI_H
#define GUI_H
#include "GUI/TextWidget.h"
#include "GUI/ButtonWidget.h"
#include "GUI/TextListWidget.h"


namespace ME {

class MedievalEngine;

class GUI : public Drawable {
public:
    GUI();
    void registerEngine(MedievalEngine* engine);

    void draw(Window& window);
    void update();
    void handleEvents(Event evt);

    void setPosition(const Vect2f& pos);
    Vect2f getPosition();
    void move(const Vect2f& pos);

    void setSize(const Vect2f& size);
    Vect2f getSize();
    void setScale(const Vect2f& scale);
    Vect2f getScale();

    void setColor(const Color &color);
    Color getColor();

    float getRotation();
    void setRotation(const float& angle);
    void rotate(const float& angle);

    Vect2f getOrigin();
    void setOrigin(const Vect2f& origin);

    Area getLocalBounds();
    Area getGlobalBounds();

    void setOpacity(const float& opacity);

    void show();
    void hide();

    bool isVisible();
    bool isActive();

    void pause();
    void play();

    WidgetPtr addWidget(const std::string& name,
                         WidgetPtr object);

    template<typename T>
    T* getWidget(const std::string& name);

protected:
    WidgetPtr findWidget(const std::string& name);

    Vect2f mRelativePostion;
    Vect2f mRelativeSize;
    Vect2f mRelativeScale;
    float mRelativeRotate;
    Color mRelativeColor;
private:
    MedievalEngine* mEngine;
    bool mIsVisible;
    bool mIsActive;

    std::map<std::string, WidgetPtr> mWidgets;
};

template<typename T>
T* GUI::getWidget(const std::string& name) {
    return static_cast<T*>(findWidget(name).get());
}

}

#endif // GUI_H

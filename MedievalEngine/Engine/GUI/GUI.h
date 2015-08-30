#ifndef GUI_H
#define GUI_H
#include <map>
#include <memory>
#include "GUI/TextWidget.h"
#include "GUI/ButtonWidget.h"
#include "GUI/TextListWidget.h"


namespace ME {

class MedievalEngine; 

class GUI {
public:
    GUI();
    void registerEngine(MedievalEngine* engine);

    void draw(Window& window);
    void update();
    void handleEvents(Event evt);

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

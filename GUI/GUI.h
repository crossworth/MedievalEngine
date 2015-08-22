#ifndef GUI_H
#define GUI_H
#include <vector>
#include <GUI/ObjectWrapper.h>
#include <GUI/TextObject.h>
#include <GUI/ButtonObject.h>
#include <GUI/TextScrollListObject.h>


namespace ME {

class GUI {
public:
    GUI(WindowInfo* windowInfo);
    void draw(Window& window);
    void update();
    void handleEvents(Event evt, Window& window);

    void show();
    void hide();

    bool isVisible();
    bool isActive();

    void pause();
    void play();

    GUIObject* addObject(const std::string& name, GUIObject* object);

    template<typename T>
    T* getObject(const std::string& name);

protected:
    GUIObject* findObject(const std::string& name);
    WindowInfo* windowInfo;
private:
    bool mIsVisible;
    bool mIsActive;
    std::vector<ObjectWrapper> mObjects;
};

template<typename T>
T* GUI::getObject(const std::string& name) {
    return static_cast<T*>(findObject(name));
}


}

#endif // GUI_H

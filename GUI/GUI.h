#ifndef GUI_H
#define GUI_H
#include <vector>
#include <GUI/ObjectWrapper.h>
#include <GUI/TextObject.h>
#include <GUI/ButtonObject.h>

namespace ME {

class GUI {
public:
    GUI(WindowInfo* windowInfo);
    void draw(Window &window);
    void update();
    void handleEvents(Event evt, Window& window);

    void show();
    void hide();

    bool isVisible();
    bool isActive();

    void pause();
    void play();

    GUIObject* addObject(GUIObject* object);
    GUIObject* getObject(const std::string name);

protected:
    GUIObject* findObject(const std::string name);
    WindowInfo* windowInfo;
private:
    bool _isVisible;
    bool _isActive;
    std::vector<ObjectWrapper> mObjects;
};

}

#endif // GUI_H

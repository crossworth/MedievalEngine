#ifndef TEXT_H
#define TEXT_H
#include "Config.h"
#include "GUIObject.h"

namespace ME {

class TextObject : public GUIObject {
public:
    TextObject(const std::string &text, const int &textSize, const std::string &font = "default");
    void update();
    void draw();
    void processEvents(Event evt);

private:
    std::string textReference;

    Text* getObject();
};

}

#endif // TEXT_H

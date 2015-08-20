#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H
#include <Assets/AssetsManager.h>
#include <Helper/ID.h>
#include <GUI/GUIObject.h>


namespace ME {

class TextObject : public GUIObject {
public:
    TextObject(const std::string &text, const int &textSize);
    void draw(Window &window);
    void update();
    void handleEvents(Event evt);

    void setPosition(const Vect2f &pos);
    Vect2f getPosition();
    Vect2f getSize();

    void onMouseOver();
    void onClick();
    void onMouseOut();

    void setOpacity(const float &opacity);
    float getOpacity();

    void setColor(const Color &color);
    Color getColor();

private:
    AssetsManager* mAssets;
    MEid mTextID;
    Text* mTextRef;
};

}

#endif // TEXT_H

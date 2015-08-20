#ifndef BUTTONOBJECT_H
#define BUTTONOBJET_H
#include <Assets/AssetsManager.h>
#include <Helper/ID.h>
#include <GUI/GUIObject.h>

namespace ME {

class ButtonObject : public GUIObject {
public:
    ButtonObject(const std::wstring& text, Vect2f pos, MEid fontID = 0);
    void draw(Window &window);
    void update();
    void handleEvents(Event evt);

    void onMouseOver();
    void onMouseOut();

    void onClick();

    void setPosition(const Vect2f &pos);
    Vect2f getPosition();

    Vect2f getSize();

    void setOpacity(const float &opacity);
    float getOpacity();

    void setColor(const Color &color);
    Color getColor();

    Area getLocalBounds();
    Area getGlobalBounds();
private:
    MEid mShapeID;
    MEid mTextID;
    Text* mTextRef;
    Shape* mShapeRef;
    Color colorGradient1;
    Color colorGradient2;
    Color colorGradientHover;
    sf::Color c1;
    sf::Color c2;
    bool _doneTransition;
};

}

#endif // BUTTONOBJET_H

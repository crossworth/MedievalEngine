#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H
#include <Helper/ID.h>
#include <Assets/AssetsManager.h>
#include <GUI/GUIObject.h>


namespace ME {

class TextObject : public GUIObject {
public:
    TextObject(const std::wstring& text, const int& textSize, const Vect2f& pos = Vect2f());
    void init();
    void draw(Window& window);
    void update();
    void handleEvents(Event evt, Window& window);

    void setPosition(const Vect2f& pos);
    Vect2f getPosition();
    Vect2f getSize();

    void onMouseOver(Event evt, Window& window);
    void onClick(Event evt, Window& window);
    void onMouseOut(Event evt, Window& window);

    void setOpacity(const float& opacity);
    float getOpacity();

    void setColor(const Color& color);
    Color getColor();

    Area getLocalBounds();
    Area getGlobalBounds();
private:
    MEid mTextID;
    Text* mTextRef;
    std::wstring mText;
    int mTextSize;
};

}

#endif // TEXT_H

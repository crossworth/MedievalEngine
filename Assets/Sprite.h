#ifndef SPRITE_H
#define SPRITE_H
#include <Assets/Asset.h>
#include <Graphics/Drawable.h>
#include <Assets/Texture.h>
#include <Helper/Vect2.h>
#include <Helper/Color.h>
#include <SFML/Graphics.hpp>
#include <LogInc.h>

namespace ME {

class Sprite : public Asset, public Drawable {
public:
    Sprite();

    sf::Sprite* getResourcePointer();

    void setTexture(Texture *texture);

    void draw(sf::RenderWindow *renderWindow);

    void setPosition(const Vect2f &pos);
    Vect2f getPosition();

    void setSize(const Vect2f &size);
    Vect2f getSize();

    void setColor(const Color &color);
    Color getColor();

private:
    sf::Sprite mSprite;
};

}

#endif // SPRITE_H

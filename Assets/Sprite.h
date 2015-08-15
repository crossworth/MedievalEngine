#ifndef SPRITE_H
#define SPRITE_H
#include <Assets/Asset.h>
#include <Graphics/Drawable.h>
#include <Assets/Texture.h>
#include <Helper/Vect2.h>
#include <Helper/Color.h>
#include <SFML/Graphics.hpp>
#include <LogInc.h>
#include <Effects/Effects.h>

namespace ME {

class Sprite : public Asset, public Drawable {
public:
    Sprite();

    sf::Sprite* getResourcePointer();

    void setTexture(Texture *texture);

    void draw(sf::RenderWindow *renderWindow);

    void setPosition(const Vect2f &pos);
    Vect2f getPosition();
    void move(const Vect2f &pos);

    void setSize(const Vect2f &size);
    Vect2f getSize();

    void setColor(const Color &color);
    Color getColor();

    float getRotation();
    void setRotation(const float &angle);
    void rotate(const float &angle);

    Vect2f getOrigin();
    void setOrigin(const Vect2f &origin);

private:
    sf::Sprite mSprite;
};

}

#endif // SPRITE_H

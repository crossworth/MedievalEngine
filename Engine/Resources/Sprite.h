#ifndef SPRITE_H
#define SPRITE_H
#include <SFML/Graphics.hpp>
#include "LogInc.h"
#include "Helper/Vect2.h"
#include "Helper/Color.h"
#include "Graphics/Drawable.h"
#include "Resources/Resource.h"
#include "Resources/Texture.h"
#include "Effects/Effect.h"


namespace ME {

class Sprite : public Resource, public Drawable {
public:
    Sprite();

    sf::Sprite* getResourcePointer();

    void setTexture(Texture* texture);

    void draw(sf::RenderWindow* renderWindow);

    void setPosition(const Vect2f& pos);
    Vect2f getPosition();
    void move(const Vect2f& pos);

    void setSize(const Vect2f& size);
    Vect2f getSize();
    void setScale(const Vect2f& scale);
    Vect2f getScale();

    void setColor(const Color& color);
    Color getColor();

    float getRotation();
    void setRotation(const float& angle);
    void rotate(const float& angle);

    Vect2f getOrigin();
    void setOrigin(const Vect2f& origin);

    Area getLocalBounds();
    Area getGlobalBounds();
private:
    sf::Sprite mSprite;
};

}

#endif // SPRITE_H

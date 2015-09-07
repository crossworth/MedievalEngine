#ifndef SPRITEANIMATION_H
#define SPRITEANIMATION_H
#include <vector>
#include <utility>
#include <SFML/Graphics.hpp>
#include "LogInc.h"
#include "Helper/Vect2.h"
#include "Helper/Color.h"
#include "Helper/Clock.h"
#include "Graphics/Drawable.h"
#include "Resources/Resource.h"
#include "Resources/Texture.h"
#include "Effects/Effect.h"


namespace ME {

class SpriteAnimation : public Resource, public Drawable {
public:
    SpriteAnimation();

    void addFrame(const int32_t& time, Texture* texture);
    void play();
    void pause();
    bool isPlaying();

    sf::Sprite* getResourcePointer();

    void draw(Window& window, sf::RenderStates* state);
    void draw(sf::RenderWindow* renderWindow, sf::RenderStates* state);

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

protected:
    void updateSprite();
private:
    bool mIsPlaying;
    sf::Sprite mSprite;
    std::vector<std::pair<unsigned int, Texture*> > mFrames;
    std::vector<std::pair<unsigned int, Texture*> >::iterator mFrameIterator;
    Clock mClock;
};

}

#endif // SPRITEANIMATION_H

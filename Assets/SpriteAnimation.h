#ifndef SPRITEANIMATION_H
#define SPRITEANIMATION_H
#include <Assets/Asset.h>
#include <Graphics/Drawable.h>
#include <Assets/Texture.h>
#include <Helper/Vect2.h>
#include <Helper/Color.h>
#include <SFML/Graphics.hpp>
#include <LogInc.h>
#include <vector>
#include <utility>
#include <Effects/Effects.h>

namespace ME {

class SpriteAnimation : public Asset, public Drawable {
public:
    SpriteAnimation();

    void addFrame(const int32_t &time, Texture *texture);
    void play();
    void pause();
    bool isPlaying();

    void draw(sf::RenderWindow *renderWindow);

    void setPosition(const Vect2f &pos);
    Vect2f getPosition();
    void move(const Vect2f &pos);

    void setSize(const Vect2f &size);
    Vect2f getSize();
    void setScale(const Vect2f &scale);
    Vect2f getScale();

    void setColor(const Color &color);
    Color getColor();

    float getRotation();
    void setRotation(const float &angle);
    void rotate(const float &angle);

    Vect2f getOrigin();
    void setOrigin(const Vect2f &origin);

private:
    bool mIsPlaying;
    sf::Sprite mSprite;
    std::vector<std::pair<unsigned int, Texture*> > mFrames;
    std::vector<std::pair<unsigned int, Texture*> >::iterator mFrameIterator;
    sf::Clock mClock;
};

}

#endif // SPRITEANIMATION_H

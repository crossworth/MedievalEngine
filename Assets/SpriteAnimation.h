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

namespace ME {

class SpriteAnimation : public Asset, public Drawable {
public:
    SpriteAnimation();

    void addFrame(const int32_t &time, Texture *texture);
    void play();
    void pause();
    bool isPlaing();

    void draw(sf::RenderWindow *renderWindow);

    void setPosition(const Vect2f &pos);
    Vect2f getPosition();

    void setSize(const Vect2f &size);
    Vect2f getSize();

    void setColor(const Color &color);
    Color getColor();

private:
    bool _isPlaying;
    sf::Sprite mSprite;
    std::vector<std::pair<unsigned int, Texture*>> mFrames;
    std::vector<std::pair<unsigned int, Texture*> >::iterator mFramesIT;
    sf::Clock mClock;
};

}

#endif // SPRITEANIMATION_H

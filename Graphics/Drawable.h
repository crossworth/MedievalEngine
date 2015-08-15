#ifndef DRAWABLE_H
#define DRAWABLE_H
#include <Helper/Vect2.h>
#include <SFML/Graphics.hpp>
#include <Helper/Color.h>
#include <LogInc.h>
#include <vector>

namespace ME {

class Effects;

class Drawable {
public:
    Drawable();

    virtual void draw(sf::RenderWindow *renderWindow) = 0;

    virtual void setPosition(const Vect2f &pos) = 0;
    virtual Vect2f getPosition() = 0;
    virtual void move(const Vect2f &pos) = 0;

    virtual void setSize(const Vect2f &size) = 0;
    virtual Vect2f getSize() = 0;

    virtual void setColor(const Color &color) = 0;
    virtual Color getColor() = 0;

    virtual float getRotation() = 0;
    virtual void setRotation(const float &angle) = 0;
    virtual void rotate(const float &angle) = 0;

    virtual Vect2f getOrigin() = 0;
    virtual void setOrigin(const Vect2f &origin) = 0;
    void setOriginCenter();

    void setOpacity(float opacity);
    float getOpacity();

    void addEffect(Effects* effect);

    // TODO: implement, get bounds
protected:
    std::vector<Effects*> mEffects;
    bool _mEffectPlay;

};

}

#endif // DRAWABLE_H

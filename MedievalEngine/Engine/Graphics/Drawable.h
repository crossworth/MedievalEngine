#ifndef DRAWABLE_H
#define DRAWABLE_H
#include <vector>
#include <memory>
#include <functional>
#include <SFML/Graphics.hpp>
#include "LogInc.h"
#include "Helper/Vect2.h"
#include "Helper/Area.h"
#include "Helper/Color.h"
#include "Helper/ColorGradient.h"


namespace ME {

class Effect;
class Window;

typedef std::shared_ptr<Effect> EffectPtr;

enum Padding { TOP, BOTTOM, LEFT, RIGHT, ALL};

class Drawable {
public:
    Drawable();
    virtual ~Drawable();

    virtual void draw(Window& window);
    virtual void draw(sf::RenderWindow* renderWindow, sf::RenderStates* state = nullptr) = 0;

    virtual void setPosition(const Vect2f& pos) = 0;
    virtual Vect2f getPosition() = 0;
    virtual void move(const Vect2f& pos);

    virtual void setSize(const Vect2f& size) = 0;
    virtual Vect2f getSize() = 0;
    virtual void setScale(const Vect2f& scale) = 0;
    virtual Vect2f getScale() = 0;

    virtual void setColor(const Color& color) = 0;
    virtual Color getColor() = 0;

    virtual float getRotation() = 0;
    virtual void setRotation(const float& angle) = 0;
    virtual void rotate(const float& angle);

    virtual Vect2f getOrigin() = 0;
    Vect2f getOriginRelative();
    virtual void setOrigin(const Vect2f& origin) = 0;

    void setOriginCenter();

    virtual Area getLocalBounds() = 0;
    virtual Area getGlobalBounds() = 0;

    void setOpacity(float opacity);
    float getOpacity();

    void addEffect(Effect* effect);

    void playEffects();
    void pauseEffects();
    bool isPlayingEffects();

    void removeEffect(std::string effectType);
    void removeAllEffects();

    // Helper method to tell if We require the Window Object insted of a RenderWindow
    // We use this to reander our GUI's object, since they require more information
    // to be able to render
    virtual bool requireWindowObject();

    void setPadding(const float& percent, Padding type = Padding::ALL);

    float mPaddingTop;
    float mPaddingBottom;
    float mPaddingRight;
    float mPaddingLeft;
protected:
    sf::RenderStates* updateEffects();
    sf::RenderStates* mRenderStates;
    std::vector<EffectPtr> mEffects;
    bool mIsEffectPlaying;
};

}

#endif // DRAWABLE_H

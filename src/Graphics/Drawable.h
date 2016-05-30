#ifndef DRAWABLE_H
#define DRAWABLE_H
#include <SFML/Graphics.hpp>
#include "LogInc.h"
#include "Helper/Types.h"
#include "Helper/Area.h"
#include "Helper/ColorGradient.h"


namespace ME {


// TODO(Pedro): Put this enum on a namespace

/**
 * The Padding enum
 * Define the position which apply the padding to a Drawable element
 */
enum Padding {
    TOP,    ///< Relative to top
    BOTTOM, ///< Relative to bottom
    LEFT,   ///< Relative to left
    RIGHT,  ///< Relative to right
    ALL     ///< All the sides
};

class Drawable {
public:
    Drawable();
    virtual ~Drawable();

    virtual void draw(Window& window) = 0;

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

    virtual void setOpacity(const float& opacity);
    float getOpacity();

    void setRenderState(sf::RenderStates renderState);
    sf::RenderStates* getRenderState();

    void addEffect(Effect* effect);

    void playEffects();
    void pauseEffects();
    bool isPlayingEffects();

    // TODO(Pedro): Test if this work
    void removeEffect(std::string effectType);
    void removeAllEffects();

    /**
     * Define the padding relative to the Window object
     * @param const float& percent - The padding percentage (max 1.0f)
     * @param Padding type - The padding type (default Padding::ALL)
     */
    void setPadding(const float& percent, Padding type = Padding::ALL);

    //TODO(Pedro): implement a setPaddingRelative
    // to set the padding relative to the current object that it reside on
    // or maybe do something different, like implement setPadding only on widget
    // objects and keep the widget a pointer to all childerns so we can update all the childerns
    // relative to the parent position or something like that

    float mPaddingTop;
    float mPaddingBottom;
    float mPaddingRight;
    float mPaddingLeft;
protected:
    // TODO(Pedro): We have to make this work more nicily
    // maybe put the RenderStates on each Drawable object
    void updateEffects();
    sf::RenderStates mRenderStates;
    std::vector<EffectPtr> mEffects;
    bool mIsEffectPlaying;
};

}

#endif // DRAWABLE_H

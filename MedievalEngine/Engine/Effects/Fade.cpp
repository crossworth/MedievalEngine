#include "Fade.h"

using namespace ME;

Fade::Fade(double time, const Type &type, VoidCallback func) {
    mType     = Effect::Type::FADE;

    // We always recive a VoidCallback
    // if the user don't supply one we just use an empty VoidCallback
    mCallback = VoidCallback(func);

    // Time in milliseconds
    mFadeTime = time;
    mFadeType = type;

    // TODO(Pedro): Enable use to set the initial value to fade out and the final value?
    // Get the value from the object?

    // Check the type and set our mFadeCounter variable
    if (mFadeType == Type::FADEOUT) {
        mFadeCounter = 255.0f;
        mFadeType    = Type::FADEOUT;
    } else {
        mFadeType    = Type::FADEIN;
        mFadeCounter = 0.0f;
    }
}

sf::RenderStates* Fade::update(Drawable* object) {
    // If the effect it's done we do nothing, just return an empty sf::RenderStates
    // Probably this will be always true since we remove the effect after it's done
    // but anyway's better safe than sorry
    if (!isDone()) {

        // Here we have to use a double/float variable to do the calc
        // otherwise the value will be cliped out
        // on the set color function the value will be cliped anyway
        // but using float/double we can make sure that we have all
        // the data until last minute
        double mStep =  (mClock.getTime() * 255) / mFadeTime;

        // This should be pretty straight forward
        // We check the fade type and do the calculations based on it
        if (mFadeType == Type::FADEOUT) {
            // if the fadetype is fadeout we decrese the mStep from our mFadeCounter variable
            mFadeCounter = mFadeCounter - mStep;

            // If we reach 0.0f we're done
            if (mFadeCounter <= 0.0f) {
                mFadeCounter = 0.0f;
                setDone();
            }
        } else {
            // same logic here, we just add instead
            mFadeCounter = mFadeCounter + mStep;
            if (mFadeCounter >= 255.0f) {
                mFadeCounter = 255.0f;
                setDone();
            }
        }
        restartClock();

        Color tmpColor = object->getColor();
        object->setColor(Color(tmpColor.red, tmpColor.green,
                               tmpColor.blue, static_cast<int>(mFadeCounter)));
    }
    // We return our sf::RenderStates object because in this particular effect we dont use it
    return mRenderStates;
}

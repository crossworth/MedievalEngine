#include "Strobe.h"

using namespace ME;

Strobe::Strobe(double time, float negativeRange, unsigned int duration, VoidCallback func) {
    mType     = Effect::Type::STROBE;
    mCallback = VoidCallback(func);

    // If we have the information that we need to do some calculations
    // You know "SCINCE BITCH!", I mean MATH...
    mIsInitialized = false;

    // The strobe time, thats means the time that we will go over all the opacity
    mStrobeTime = time;

    // The strobe duration
    // TODO(Pedro): infinit mode?
    mDuration = duration;

    // Which direction we are going
    mDirection = -1;

    // The max value that we can go until we change directions
    // This value should be normalize from 0.0f to 1.0f
    mNegativeRange = negativeRange;

    mClockDuration.restart();

    // Max range 1.0f
    if (mNegativeRange > 1.0f) {
        mNegativeRange = 1.0f;
    }

    // Min range 0.0f;
    if (mNegativeRange < 0.0f) {
        mNegativeRange = 0.0f;
    }

    // TODO(Pedro): Why do we have an 1.0f here?
    mNegativeRange = 1.0f - mNegativeRange;
}

sf::RenderStates* Strobe::update(Drawable* object) {
    // Since we only have access to the object on the update function we
    // verify if we are initialized and if not we just fill some variables
    // TODO(Pedro): How this work with multiple Drawable objects and only one effect?
    // It keeps updating the baseColor from the other objects? How avoid it?
    if (!mIsInitialized) {
        mBaseColor     = object->getColor();
        mIsInitialized = true;
        mStrobeCounter = static_cast<float>(mBaseColor.alpha);
        restartClock();
    }

    // Since this effect don't have a done mark
    // we just wait until the time has passed by
    // and set it to done
    if (mClockDuration.getMilliSeconds() >= mDuration) {
        // TODO(Pedro): Should we reset it's values to the default?
        // Or leave at it is? Maybe we could verify if the duration has been reach and
        // that the mStrobeCounter is greater than some value or less than some value
        setDone();
    }

    // TODO(Pedro): Should we put all the code inside this if?
    // Maybe we can gain some speed or just to make the code looks more organized
    if (!isDone()) {
        // Calculate the step based on the time and the base alpha color plus the strobe time
        float mStep =  (mClock.getMilliSeconds() * mBaseColor.alpha) / static_cast<float>(mStrobeTime);

        // We check our direction
        if (mDirection < 0) {
            // Nothing much different from the fade effect
            mStrobeCounter = mStrobeCounter - mStep;

            if (mStrobeCounter <= static_cast<float>(mBaseColor.alpha * mNegativeRange)) {
                mStrobeCounter = static_cast<float>(mBaseColor.alpha * mNegativeRange);
                mDirection     = 1;
            }
        } else {
            mStrobeCounter = mStrobeCounter + mStep;

            if (mStrobeCounter >= mBaseColor.alpha) {
                mStrobeCounter = static_cast<float>(mBaseColor.alpha);
                mDirection     = -1;
            }
        }
        restartClock();

        Color tmpColor = object->getColor();
        object->setColor(Color(tmpColor.red, tmpColor.green, tmpColor.blue,
                               static_cast<int>(mStrobeCounter)));
    }
    // We return our sf::RenderStates object because in this particular effect we dont use it
    return mRenderStates;
}

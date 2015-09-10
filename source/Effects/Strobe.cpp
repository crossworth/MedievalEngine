#include "Strobe.h"

using namespace ME;

Strobe::Strobe(unsigned int time, float negativeRange, unsigned int duration, VoidCallback func) : mDuration(0) {
    mType     = Effect::Type::STROBE;
    mCallback = VoidCallback(func);

    // If we have the information that we need to do some calculations
    // You know "SCINCE BITCH!", I mean MATH...
    mIsInitialized = false;

    // The strobe time, thats means the time that we will go over all the opacity
    mStrobeTime = static_cast<float>(time);

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

    // We subtrack by 1.0f to convert the value
    // if the user pass 0.9f he wants to go from 10% until 100%
    // so doing 1.0f - 0.9f we can get the number 0.1f that we will
    // use to calcule the correct opacity
    mNegativeRange = 1.0f - mNegativeRange;
}

void Strobe::update(Drawable* object) {
    if (!isDone()) {
        // Since we only have access to the object on the update function we
        // verify if we are initialized and if not we just fill some variables

        if (!mIsInitialized) {
            mIsInitialized = true;
            mBaseColor     = object->getColor();
            mStrobeCounter = static_cast<float>(mBaseColor.alpha);
            restartClock();
        }

        // Since this effect don't have a done mark
        // we just wait until the time has passed by 
        // if the mDuration it's not -1 (which is infinity)
        // and  then set it to done after we get to our normal state (initial state)
        if (mDuration != -1 && mClockDuration.getMilliSeconds() >= mDuration && 
            mStrobeCounter >= static_cast<float>(mBaseColor.alpha)) {
            setDone();
        }
    
        // Calculate the step based on the time and the base alpha color plus the strobe time
        float mStep =  (mClock.getMilliSeconds() * mBaseColor.alpha) / mStrobeTime;

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

        object->setOpacity(static_cast<float>(mStrobeCounter) / 255);
    }
}

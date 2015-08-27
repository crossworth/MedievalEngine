#include "Strobe.h"

using namespace ME;

Strobe::Strobe(unsigned int time, float negativeRange, unsigned int duration, Effect::Callback func) {
    mType     = Effect::Type::STROBE;
    mCallback = Effect::Callback(func);

    mIsInitialized = false;
    mStrobeTime    = time;
    mDuration      = duration;
    mDirection     = -1;
    mNegativeRange = negativeRange;

    mClockDuration.restart();

    if (mNegativeRange > 1.0f) {
        mNegativeRange = 1.0f;
    }

    if (mNegativeRange < 0.0f) {
        mNegativeRange = 0.0f;
    }

    mNegativeRange = 1.0f - mNegativeRange;
}

void Strobe::update(Drawable* object) {
    if (!mIsInitialized) {
        mBaseColor     = object->getColor();
        mIsInitialized = true;
        mStrobeCounter = mBaseColor.alpha;
        restartClock();
    }

    if (mClockDuration.getTime() >= mDuration) {
        setDone();
    }

    if (!isDone()) {

        float mStep =  (mClock.getTime() * mBaseColor.alpha) / mStrobeTime;

        if (mDirection < 0) {
            mStrobeCounter = mStrobeCounter - mStep;

            if (mStrobeCounter <= static_cast<float>(mBaseColor.alpha * mNegativeRange)) {
                mStrobeCounter = static_cast<float>(mBaseColor.alpha * mNegativeRange);
                mDirection     = 1;
            }
        } else {
            mStrobeCounter = mStrobeCounter + mStep;

            if (mStrobeCounter >= mBaseColor.alpha) {
                mStrobeCounter = mBaseColor.alpha;
                mDirection     = -1;
            }
        }
        restartClock();

        Color tmpColor = object->getColor();
        object->setColor(Color(tmpColor.red, tmpColor.green, tmpColor.blue,
                               static_cast<int>(mStrobeCounter)));
    }
}

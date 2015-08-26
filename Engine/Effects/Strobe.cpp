#include "Strobe.h"

using namespace ME;

Strobe::Strobe(unsigned int time, float negativeRange) {
    mType = Effect::Type::STROBE;

    mIsInitialized = false;
    mStrobeTime    = time;
    mDirection     = -1;
    mNegativeRange = negativeRange;

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
        resetClock();
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
        resetClock();

        Color tmpColor = object->getColor();
        object->setColor(Color(tmpColor.red, tmpColor.green, tmpColor.blue,
                               static_cast<int>(mStrobeCounter)));
    }
}

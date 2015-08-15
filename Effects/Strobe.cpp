#include "Strobe.h"

using namespace ME;

Strobe::Strobe(float time, float negativeRange) {
    mType = "strobe";

    _initialized   = false;
    mTimeAn        = time;
    _direction     = -1;
    mNegativeRange = negativeRange;

    if (mNegativeRange > 1.0f) {
        mNegativeRange = 1.0f;
    }

    if (mNegativeRange < 0.0f) {
        mNegativeRange = 0.0f;
    }

    mNegativeRange = 1.0f - mNegativeRange;
}

bool Strobe::done() {
    return mDone;
}

void Strobe::update(Drawable *object) {
    if (!_initialized) {
        _baseColor   = object->getColor();
        _initialized = true;
        mFadeCounter = _baseColor.alpha;
        mClock.restart();
    }

    if (!done()) {
        sf::Time mTime = mClock.getElapsedTime();

        float mStep =  (mTime.asSeconds() * _baseColor.alpha)/mTimeAn;

        if (_direction < 0) {
            mFadeCounter = mFadeCounter - mStep;

            if (mFadeCounter <= static_cast<float>(_baseColor.alpha * mNegativeRange)) {
                mFadeCounter = static_cast<float>(_baseColor.alpha * mNegativeRange);
                _direction   = 1;
            }
        } else {
            mFadeCounter = mFadeCounter + mStep;

            if (mFadeCounter >= _baseColor.alpha) {
                mFadeCounter = _baseColor.alpha;
                _direction   = -1;
            }
        }
        mClock.restart();

        Color tmpColor = object->getColor();
        object->setColor(Color(tmpColor.red, tmpColor.green, tmpColor.blue, static_cast<int>(mFadeCounter)));
    }
}

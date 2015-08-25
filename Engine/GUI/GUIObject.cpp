#include "GUIObject.h"

using namespace ME;

GUIObject::GUIObject() : mIsVisible(true), mIsActive(true) {
    mDefaultFontID = Font::DEFAULT_FONT;
}

void GUIObject::registerAssetsManager(AssetsManager* assets) {
    mAssets = assets;
}

bool GUIObject::isVisible() {
    return mIsVisible;
}

bool GUIObject::isActive() {
    return mIsActive;
}

bool GUIObject::isColorGradient() {
    return mHasColorGradient;
}

std::string GUIObject::getType() {
    return mType;
}

Vect2f GUIObject::getPosition() {
    return mPos;
}

float GUIObject::getOpacity() {
    return mOpacity;
}

Color GUIObject::getColor() {
    return mColor;
}

void GUIObject::hide() {
    mIsVisible = false;
}

void GUIObject::onMouseOver(Event evt, Window& window) {

}

void GUIObject::onMouseOut(Event evt, Window& window) {

}

void GUIObject::onClick(Event evt, Window& window) {

}

void GUIObject::show() {
    mIsVisible = true;
}

void GUIObject::setPosition(const Vect2f& pos) {
    mPos.x = pos.x;
    mPos.y = pos.y;
}

void GUIObject::setOpacity(const float& opacity) {
    mOpacity = opacity;
}

void GUIObject::setColor(const Color& color) {
    mColor.red   = color.red;
    mColor.green = color.green;
    mColor.blue  = color.blue;
    mColor.alpha = color.alpha;
}
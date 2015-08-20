#include "GUIObject.h"

using namespace ME;

GUIObject::GUIObject() : _isVisible(true), _isActive(true) {
    mAssets       = AssetsManager::getInstance();
    defaultFontID = mAssets->loadFont("font/YanoneKaffeesatz-Regular.ttf");
}

bool GUIObject::isVisible() {
    return _isVisible;
}

bool GUIObject::isActive() {
    return _isActive;
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
    _isVisible  = false;
}

void GUIObject::onMouseOver() {

}

void GUIObject::onMouseOut() {

}

void GUIObject::onClick() {

}

void GUIObject::show() {
    _isVisible  = true;

}

void GUIObject::setPosition(const Vect2f &pos) {
    mPos.x = pos.x;
    mPos.y = pos.y;
}

void GUIObject::setOpacity(const float &opacity) {
    mOpacity = opacity;
}

void GUIObject::setColor(const Color &color) {
    mColor.red = color.red;
    mColor.green = color.green;
    mColor.blue = color.blue;
    mColor.alpha = color.alpha;
}

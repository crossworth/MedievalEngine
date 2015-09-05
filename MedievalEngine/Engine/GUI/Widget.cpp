#include "Widget.h"

using namespace ME;

Widget::Widget() : mIsVisible(true), mIsActive(true), mOpacity(1.f) {
    mDefaultFontID = Font::DEFAULT_FONT;
}

void Widget::registerResourceManager(ResourceManager* resource) {
    mResources = resource;
}

void Widget::registerWindow(Window* window) {
    mWindow = window;
}

void Widget::draw(sf::RenderWindow* renderWindow) {

}

bool Widget::isVisible() {
    return mIsVisible;
}

bool Widget::isActive() {
    return mIsActive;
}

void Widget::setEnable(bool active) {
    mIsActive = active;
}

bool Widget::isColorGradient() {
    return mHasColorGradient;
}

std::string Widget::getType() {
    return mType;
}

Vect2f Widget::getPosition() {
    return mPos;
}

float Widget::getOpacity() {
    return mOpacity;
}

Color Widget::getColor() {
    return mColor;
}

void Widget::hide() {
    mIsVisible = false;
}

void Widget::show() {
    mIsVisible = true;
}

void Widget::setPosition(const Vect2f& pos) {
    mPos.x = pos.x;
    mPos.y = pos.y;
}

void Widget::setOpacity(const float& opacity) {
    mOpacity = opacity;
}

void Widget::setColor(const Color& color) {
    mColor.red   = color.red;
    mColor.green = color.green;
    mColor.blue  = color.blue;
    mColor.alpha = color.alpha;
}

Window* Widget::getWindow() {
    return mWindow;
}

ResourceManager* Widget::getResourceManager() {
    return mResources;
}

void Widget::addEventHandle(GUIEventPtr event) {
    LOG << Log::VERBOSE << "[Widget::addEventHandle] New GUIEvent attached to widget "
        << getType() << std::endl;
    mEvents.push_back(event);
}

void Widget::removeEventHandle(GUIEventPtr event) {
    auto eventsIt = std::find(mEvents.begin(), mEvents.end(), event);

    if (eventsIt != mEvents.end()) {
        LOG << Log::VERBOSE << "[Widget::removeEventHandle] New GUIEvent attached to widget "
            << getType() << std::endl;
        mEvents.remove(event);
    }
}

void Widget::notify(GUIEvent::Type type, Widget* widget) {
    for(auto it = mEvents.begin(); it != mEvents.end(); it++) {
        (*it)->notify(type, widget);
    }
}

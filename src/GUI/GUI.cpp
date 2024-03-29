#include <Engine/MedievalEngine.h>
#include "GUI.h"

using namespace ME;

GUI::GUI() : mIsVisible(true), mIsActive(true) {
    LOG << Log::VERBOSE << "[GUI::GUI] GUI created" << std::endl;
}

void GUI::registerEngine(MedievalEngine* engine) {
    mEngine = engine;
}

void GUI::draw(Window& window) {
    if (isVisible()) {
        updateEffects();
        for(auto it = mWidgets.begin(); it != mWidgets.end(); it++) {
            if ((*it).second->isVisible()) {
                (*it).second->setRenderState(mRenderStates);
                (*it).second->draw(window);
            }
        }
    }
}

void GUI::handleEvents(Event evt) {
    if (this->isActive()) {

        for(auto it = mWidgets.begin(); it != mWidgets.end(); it++) {
            if ((*it).second->isActive()) {
                (*it).second->handleEvents(evt);
            }
        }
    }
}

void GUI::show() {
    mIsVisible = true;
    LOG << Log::VERBOSE << "[GUI::show]" << std::endl;
}

void GUI::hide() {
    mIsVisible = false;
    LOG << Log::VERBOSE << "[GUI::hide]" << std::endl;
}

void GUI::play() {
    mIsActive = true;
    LOG << Log::VERBOSE << "[GUI::play]" << std::endl;
}

void GUI::pause() {
    mIsActive = false;
    LOG << Log::VERBOSE << "[GUI::pause]" << std::endl;
}

bool GUI::isActive() {
    return mIsActive;
}

bool GUI::isVisible() {
    return mIsVisible;
}

void GUI::update() {
    if (isActive()) {
        for(auto it = mWidgets.begin(); it != mWidgets.end(); it++) {
            (*it).second->update();
        }
    }
}

WidgetPtr GUI::addWidget(const std::string& name, WidgetPtr object) {
   if (findWidget(name) != nullptr) {
       LOG << Log::WARNING << "[GUI::addWidget] GUI Widget " + object->getType()
           <<  " " +  name + " already added" << std::endl;

       object = mWidgets[name];
       return findWidget(name);
   }

    mWidgets[name] = object;
    mWidgets[name]->registerWindow(mEngine->getWindow());
    mWidgets[name]->init();

    LOG << Log::VERBOSE << "[GUI::addWidget] GUI Widget " + object->getType()
        <<  " " +  name + " added" << std::endl;

    return mWidgets[name];
}

WidgetPtr GUI::findWidget(const std::string& name) {
    if (mWidgets.find(name) != mWidgets.end()) {
        return mWidgets[name];
    }

    LOG << Log::WARNING << "[GUI::findWidget] GUI Widget " +  name + " not found"
        << std::endl;

    return nullptr;
}

void GUI::setPosition(const Vect2f& pos) {
    mRelativePostion = pos;
}

Vect2f GUI::getPosition() {
    return mRelativePostion;
}

void GUI::move(const Vect2f& pos) {
    mRelativePostion = Vect2f(mRelativePostion.x + pos.x , mRelativePostion.y + pos.y);

}

void GUI::setSize(const Vect2f& size) {
    mRelativeSize = size;
}

Vect2f GUI::getSize() {
    return mRelativeSize;
}

void GUI::setScale(const Vect2f& scale) {
    mRelativeScale = scale;

}

Vect2f GUI::getScale() {
	return mRelativeScale;
}

void GUI::setColor(const Color& color) {
    mRelativeColor = color;

    for(auto it = mWidgets.begin(); it != mWidgets.end(); it++) {
        (*it).second->setColor(mRelativeColor);
    }
}

Color GUI::getColor() {
    return mRelativeColor;
}

float GUI::getRotation() {
    return mRelativeRotate;
}

void GUI::setRotation(const float& angle) {
    mRelativeRotate = angle;
    // TODO(Pedro):implement this
}

void GUI::rotate(const float& angle) {
    // TODO(Pedro): implement this the right way
    mRelativeRotate = angle;

}

Vect2f GUI::getOrigin() {
    // TODO(Pedro): implement this the right way
    return Vect2f(0.f, 0.f);
}

void GUI::setOrigin(const Vect2f& origin) {
    // TODO(Pedro):implement this
}

Area GUI::getLocalBounds() {
    // TODO(Pedro):implement this
    return Area(0.f, 0.f, 1200.f, 700.f);
}

Area GUI::getGlobalBounds() {
    // TODO(Pedro):implement this
    return Area(0.f, 0.f, 1200.f, 700.f);
}

void GUI::setOpacity(const float& opacity) {
    for(auto it = mWidgets.begin(); it != mWidgets.end(); it++) {
        (*it).second->setOpacity(opacity);
    }
}
#include "GUI.h"
#include <Engine/MedievalEngine.h>

using namespace ME;

GUI::GUI() : mIsVisible(true), mIsActive(true) {
    LOG << Log::VERBOSE << "[GUI::GUI] GUI created" << std::endl;
}

void GUI::registerEngine(MedievalEngine* engine) {
    mEngine = engine;
}

void GUI::draw(Window& window) {
    if (isVisible()) {
        for(auto it = mWidgets.begin(); it != mWidgets.end(); it++) {
            if ((*it).second->isVisible()) {
                (*it).second->draw(window);
            }   
        }
    }
}

void GUI::handleEvents(Event evt) {
    if (this->isActive()) {

        Vect2i mousePos = Mouse::getPosition(mEngine->getWindow());

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
       return findWidget(name);
   }

    mWidgets[name] = object;
    mWidgets[name]->registerResourceManager(mEngine->getResourceManager());
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

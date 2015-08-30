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
    if (mIsVisible) {
        for(unsigned int i = 0; i < mObjects.size(); i++) {
            mObjects[i].object->draw(window);
        }
    }
}

void GUI::handleEvents(Event evt, Window& window) {
    if (mIsActive) {
        for(unsigned int i = 0; i < mObjects.size(); i++) {
            mObjects[i].object->handleEvents(evt, window);
        }

        Vect2i mousePos = Mouse::getPosition(*window.getWindowPtr());

        for(unsigned int i = 0; i < mObjects.size(); i++) {
            if (mObjects[i].object->getGlobalBounds().contains(mousePos)) {
                mObjects[i].isMouseOver = true;
                mObjects[i].object->onMouseOver(evt, window);
            }

            if (mObjects[i].object->getGlobalBounds().contains(mousePos) &&
                Mouse::isButtonPressed(Mouse::Button::Left) ) {
                mObjects[i].object->onClick(evt, window);
            }

            if (!(mObjects[i].object->getGlobalBounds().contains(mousePos)) &&
                mObjects[i].isMouseOver) {
                mObjects[i].isMouseOver = false;
                mObjects[i].object->onMouseOut(evt, window);
            }
        }
    }
}

void GUI::show() {
    mIsVisible = true;
}

void GUI::hide() {
    mIsVisible = false;
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
    if (mIsActive) {
        for(unsigned int i = 0; i < mObjects.size(); i++) {
            mObjects[i].object->update();
        }
    }
}

GUIObject* GUI::addObject(const std::string& name, GUIObject* object) {
   if (findObject(name) != nullptr) {
       return findObject(name);
   }

    object->registerAssetsManager(mEngine->getResourceManager());
    object->init();

    ObjectWrapper objTmp;
    objTmp.name        = name;
    objTmp.object      = object;
    objTmp.isMouseOver = false;

    mObjects.push_back(objTmp);
    LOG << Log::VERBOSE << "[GUI::addObject] GUI Object " + object->getType()
        <<  " " +  name + " added" << std::endl;

    return mObjects[mObjects.size() - 1].object;
}

GUIObject* GUI::findObject(const std::string& name) {
    for(unsigned int i = 0; i < mObjects.size(); i++) {
        if (mObjects[i].name == name) {
            return mObjects[i].object;
        }
    }

    LOG << Log::WARNING << "[GUI::findObject] GUI Object " +  name + " not found"
        << std::endl;

    return nullptr;
}

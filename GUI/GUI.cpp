#include "GUI.h"

using namespace ME;

GUI::GUI(WindowInfo* windowInfo) : _isVisible(true), _isActive(true) {
    this->windowInfo = windowInfo;

    LOG << Log::VERBOSE << "[GUI::GUI] GUI created" << std::endl;
}

void GUI::draw(Window& window) {

    if (_isVisible) {
        for(unsigned int i = 0; i < mObjects.size(); i++) {
            mObjects[i].object->draw(window);
        }
    }
}

void GUI::handleEvents(Event evt, Window& window) {
    if (_isActive) {
        for(unsigned int i = 0; i < mObjects.size(); i++) {
            mObjects[i].object->handleEvents(evt);
        }
    }

    Vect2i mousePos = Mouse::getPosition(*window.getWindowPtr());

    for(unsigned int i = 0; i < mObjects.size(); i++) {
        if (mObjects[i].object->getGlobalBounds().contains(mousePos)) {
            mObjects[i].isMouseOver = true;
            mObjects[i].object->onMouseOver();
        }

        if (mObjects[i].object->getGlobalBounds().contains(mousePos) &&
            Mouse::isButtonPressed(Mouse::Button::Left) ) {
            mObjects[i].object->onClick();
        }

        if (!(mObjects[i].object->getGlobalBounds().contains(mousePos))) {
            mObjects[i].isMouseOver = false;
            mObjects[i].object->onMouseOut();
        }
    }
}

void GUI::show() {
    _isVisible = true;
}

void GUI::hide() {
    _isVisible = false;
}

void GUI::play() {
    _isActive = true;
    LOG << Log::VERBOSE << "[GUI::play]" << std::endl;
}

void GUI::pause() {
    _isActive = false;
    LOG << Log::VERBOSE << "[GUI::pause]" << std::endl;
}

bool GUI::isActive() {
    return _isActive;
}

bool GUI::isVisible() {
    return _isVisible;
}

void GUI::update() {
    if (_isActive) {
        for(unsigned int i = 0; i < mObjects.size(); i++) {
            mObjects[i].object->update();
        }
    }
}

GUIObject* GUI::addObject(const std::string& name, GUIObject *object) {
    if (findObject(name) != nullptr) {
        return findObject(name);
    }

    ObjectWrapper objTmp;
    objTmp.name        = name;
    objTmp.object      = object;
    objTmp.isMouseOver = false;

    mObjects.push_back(objTmp);
    return mObjects.end()->object;
}


GUIObject* GUI::getObject(const std::string& name) {
    return findObject(name);
}


GUIObject* GUI::findObject(const std::string& name) {
    for(unsigned int i = 0; i < mObjects.size(); i++) {
        if (mObjects[i].name == name) {
            return mObjects[i].object;
        }
    }

    LOG << Log::WARNING << ("[GUI::findObject] GUI Object " +  name + " not found").c_str() << std::endl;
    return nullptr;
}

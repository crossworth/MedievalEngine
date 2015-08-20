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

void GUI::handleEvents(Event evt, Window &window) {
    if (_isActive) {
        for(unsigned int i = 0; i < mObjects.size(); i++) {
            mObjects[i].object->handleEvents(evt);
        }
    }

    Vect2i mousePos = Mouse::getPosition(*window.getWindowPtr());

    for(unsigned int i = 0; i < mObjects.size(); i++) {
        Vect2f objPos  = mObjects[i].object->getPosition();
        Vect2f objSize = mObjects[i].object->getSize();

        if (mousePos.x >= objPos.x && mousePos.x <= objPos.x + objSize.x &&
            mousePos.y >= objPos.y && mousePos.y <= objPos.y + objSize.y ) {
            mObjects[i].isMouseOver = true;
            mObjects[i].object->onMouseOver();
        }

        if ((mousePos.x >= objPos.x && mousePos.x <= objPos.x + objSize.x &&
            mousePos.y >= objPos.y && mousePos.y <= objPos.y + objSize.y) &&
            Mouse::isButtonPressed(Mouse::Button::Left) ) {
//            mObjects[i].object->onClick();
            std::cout << "M: " << mousePos.x << ", " << mousePos.y;
            std::cout << " O: " << objPos.y << ", " << objPos.y + objSize.y << std::endl;
        }

        if (!(mousePos.x >= objPos.x && mousePos.x <= objPos.x + objSize.x &&
            mousePos.y >= objPos.y && mousePos.y <= objPos.y + objSize.y ) &&
            mObjects[i].isMouseOver == true ) {
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

GUIObject* GUI::addObject(GUIObject *object) {
    ObjectWrapper objTmp;
    objTmp.object      = object;
    objTmp.isMouseOver = false;

    mObjects.push_back(objTmp);
    return mObjects.end()->object;
}


GUIObject* GUI::getObject(const std::string name) {
    return findObject(name);
}


GUIObject* GUI::findObject(const std::string name) {
    return nullptr;
//    if (mObjects.find(name) != mObjects.end()) {
//        return mObjects[name];
//    } else {
//        LOG << Log::WARNING << ("[GUI::findObject] GUI Object " +  name + " not found").c_str() << std::endl;
//        return nullptr;
//    }
}

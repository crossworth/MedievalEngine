//#include "GUI.h"

//using namespace ME;

//GUI::GUI() : _isVisible(true), _isActive(true) {
//    dbg = Debugger::getInstance();
//}

//void GUI::draw() {
//    if (_isVisible) {
//        for(auto it = mObjects.begin(); it != mObjects.end(); it++) {
//            (*it).second->draw();
//        }
//    }
//}

//void GUI::processEvents(Event evt) {
//    if (_isActive) {
//        for(auto it = mObjects.begin(); it != mObjects.end(); it++) {
//            (*it).second->processEvents(evt);
//        }
//    }
//}

//void GUI::show() {
//    _isVisible = true;
//}

//void GUI::hide() {
//    _isVisible = false;
//}

//void GUI::play() {
//    _isActive = true;
//}

//void GUI::pause() {
//    _isActive = false;
//}

//bool GUI::isActive() {
//    return _isActive;
//}

//bool GUI::isVisible() {
//    return _isVisible;
//}

//void GUI::update() {
//    if (_isActive) {
//        for(auto it = mObjects.begin(); it != mObjects.end(); it++) {
//            (*it).second->update();
//        }
//    }
//}

//GUIObject* GUI::addObject(const std::string name, GUIObject *object) {
//    if (mObjects.find(name) != mObjects.end()) {
//        dbg->log(WARNING, 1, ("[GUI::addObject] GUI Object " +  name + " already loaded").c_str());
//    } else {
//        mObjects[name] = object;
//    }

//    return mObjects[name];
//}


//GUIObject* GUI::getObject(const std::string name) {
//    return findObject(name);
//}


//GUIObject* GUI::findObject(const std::string name) {
//    if (mObjects.find(name) != mObjects.end()) {
//        return mObjects[name];
//    } else {
//        dbg->log(WARNING, 1, ("[GUI::findObject] GUI Object " +  name + " not found").c_str());
//        return nullptr;
//    }
//}

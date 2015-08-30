#include "GUIEvent.h"


using namespace ME;

GUIEvent::GUIEvent() {

}

void GUIEvent::setOnClick(WidgetCallback callback) {
    mCallbacks[GUIEvent::Type::onClick] = callback;
    LOG << Log::VERBOSE << "[GUIEvent::setOnClick] New event attached to widget" 
        << std::endl;
}

void GUIEvent::setOnMouseOut(WidgetCallback callback) {
    mCallbacks[GUIEvent::Type::onMouseOut] = callback;
    LOG << Log::VERBOSE << "[GUIEvent::setOnMouseOut] New event attached to widget" 
        << std::endl;
}

void GUIEvent::setOnMouseOver(WidgetCallback callback) {
    mCallbacks[GUIEvent::Type::onMouseOver] = callback;
    LOG << Log::VERBOSE << "[GUIEvent::setOnMouseOver] New event attached to widget" 
        << std::endl;
}

void GUIEvent::setOnTextEntered(WidgetCallback callback) {
    mCallbacks[GUIEvent::Type::onTextEntered] = callback;
    LOG << Log::VERBOSE << "[GUIEvent::setOnTextEntered] New event attached to widget"
        << std::endl;
}

void GUIEvent::notify(GUIEvent::Type& type, Widget* widget) {
    if (mCallbacks.find(type) != mCallbacks.end()) {
        mCallbacks[type](widget);
        LOG << Log::VERBOSE << "[GUIEvent::notify] New event notified" << std::endl;
    }
}
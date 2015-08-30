#ifndef OBJECTWRAPPER_H
#define OBJECTWRAPPER_H
#include "Helper/Types.h"
#include "GUI/GUIObject.h"


namespace ME {

class ObjectWrapper {
public:
    std::string name;
    GUIObject* object;
    bool isMouseOver;
    ObjectWrapperCallback mouseOver;
    ObjectWrapperCallback mouseClick;
    ObjectWrapperCallback mouseOut;
    ObjectWrapperCallback mouseHover;
    ObjectWrapperCallback mouseMove;
    ObjectWrapperCallback textEntered;
    // TODO(Pedro): Add new functionality
    // ObjectWrapperCallback onSelect;  
};

}


#endif // OBJECTWRAPPER_H

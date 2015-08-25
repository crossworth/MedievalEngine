#ifndef OBJECTWRAPPER_H
#define OBJECTWRAPPER_H
#include <GUI/GUIObject.h>

namespace ME {

class ObjectWrapper {
public:
    std::string name;
    GUIObject* object;
    bool isMouseOver;
};

}

#endif // OBJECTWRAPPER_H

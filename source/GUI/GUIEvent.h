#ifndef GUIEVENT_H
#define GUIEVENT_H
#include <map>
#include <memory>
#include "Helper/Types.h"
#include "LogInc.h"


namespace ME {


// TODO(Pedro): Move this out of here
class GUIEvent;
class Widget;

typedef std::shared_ptr<GUIEvent> GUIEventPtr;

class GUIEvent {
public:
    enum Type {onClick, onHover, onMouseOut, onMouseOver, onTextEntered};
public:
    GUIEvent();

    void setOnClick(WidgetCallback callback);

    void setOnMouseOut(WidgetCallback callback);
    void setOnMouseOver(WidgetCallback callback);

    void setOnTextEntered(WidgetCallback callback );

    void notify(GUIEvent::Type& type, Widget* widget);
protected:
    std::map<GUIEvent::Type, WidgetCallback> mCallbacks;
};

}

#endif // GUIEVENT_H

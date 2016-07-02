#ifndef HELPER_TYPES_H_
#define HELPER_TYPES_H_
#include <ctime>
#include <cstdio>
#include <functional>
#include <memory>

#include "Helper/BasicTypes.h"


/**
 * Define an empty void lambda function <br>
 * NOTE(Pedro): Since we are using lambda functions, we require C++11<br>
 */
#define EMPTY_VOID_CALLBACK [] (void) {}

namespace ME {


class Effect;
class Window;
class Widget;
class TextWidget;
class TextListWidget;
class GUIEvent;
class ButtonWidget;
class Resource;



/**
 * The ME::ResourceID type used on all the ME::Resource and ME::ResourceManager
 */
typedef unsigned long int ResourceID;



// TODO(Pedro): rework on the GUI system

/**
 * Define the ME::WidgetPtr with a shared pointer to a ME::Widget
 */
typedef std::shared_ptr<Widget> WidgetPtr;

/**
 * Define the ME::VoidCallback with a function pointer
 */
typedef std::function<void(void)> VoidCallback;

/**
 * Define the ME::WidgetCallback with a function pointer
 */
typedef std::function<void(Widget*)> WidgetCallback;

/**
 * Define the ME::EffectPtr with a shared pointer to a ME::Effect
 */
typedef std::shared_ptr<Effect> EffectPtr;

/**
 * Define the ME::TextWdigetPtr with a shared pointer to a ME::TextWidget
 */
typedef std::shared_ptr<TextWidget> TextWidgetPtr;

/**
 * Define the TextListWidgetPtr with a shared pointer to a ME::TextListWidget
 */
typedef std::shared_ptr<TextListWidget> TextListWidgetPtr;

/**
 * Define the ME::GUIEVentPtr with a shared pointer to a ME::GUIEvent
 */
typedef std::shared_ptr<GUIEvent> GUIEventPtr;

/**
 * Define the ME::ButtonWidgetPtr with a shared pointer to a ME::ButtonWidget
 */
typedef std::shared_ptr<ButtonWidget> ButtonWidgetPtr;


}


#endif // HELPER_TYPES_H_

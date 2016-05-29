#ifndef KEYMAPPER_H
#define KEYMAPPER_H
#include <string>
#include <algorithm>
#include "Config.h"
#include "Helper/Kit.h"
#include "Helper/CFGParser.h"
#include "Events/Event.h"


namespace ME {

class KeyMapper {
private:
    struct KeyWrapper {
        std::vector<Keyboard::KEY> keys;
        bool alt;
        bool control;
        bool shift;
        bool system;
    };

public:
    static void loadKeyMapper();
    static bool action(const std::string& actionName, Event& evt);
    static Keyboard::KEY stringToKey(const std::string& keyname);
    static KeyWrapper getKeyMapped(const std::string& actionName);

    // TODO(pedro): save to file the user custom keys
private:
    static bool mInitialized;
    static std::map<std::string, KeyWrapper> mKeys;
    static std::map<std::string, KeyWrapper> mDefaultKeys;
};

}

#endif // KEYMAPPER_H
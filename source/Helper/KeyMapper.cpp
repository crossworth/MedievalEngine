#include "KeyMapper.h"

using namespace ME;


std::map<std::string, KeyMapper::KeyWrapper> KeyMapper::mKeys;
std::map<std::string, KeyMapper::KeyWrapper> KeyMapper::mDefaultKeys;
bool KeyMapper::mInitialized = false;

void KeyMapper::loadKeyMapper() {
    KeyMapper::mInitialized = true;

    CFGParser keysFile;
    keysFile.readFile(ENGINE_DEFAULTS::DEFAULT_KEY_MAPPER);

    for(auto it : keysFile.getContents()) {
        std::string str = it.second;
        KeyMapper::KeyWrapper tmp = {};

        std::transform(str.begin(), str.end(), str.begin(), ::tolower); // to lower
        str.erase(std::remove(str.begin(), str.end(), ' '), str.end()); // erase spaces

        size_t posCut;

        if ((posCut = str.find("alt+")) != std::string::npos) {
            tmp.alt = true;
            // position of the first char plus the length
            str = str.substr(posCut + 4);
        }

        if ((posCut = str.find("ctrl+")) != std::string::npos) {
            tmp.control = true;
            // position of the first char plus the length
            str = str.substr(posCut + 5);
        }

        if ((posCut = str.find("shift+")) != std::string::npos) {
            tmp.shift = true;
            // position of the first char plus the length
            str = str.substr(posCut + 6);
        }

        if ((posCut = str.find("system+")) != std::string::npos) {
            tmp.system = true;
            // position of the first char plus the length
            str = str.substr(posCut + 7);
        }

        auto strings = Kit::explode(str, '+');

        for(auto it : strings) {
            tmp.keys.push_back(KeyMapper::stringToKey(it));    
        }

        KeyMapper::mKeys[it.first] = tmp;
    }

    // the defaults keys
    // KeyMapper::mDefaultKeys["toggle_console"] = KeyMapper::KeyWrapper { std::vector<Keyboard::KEY>(Keyboard::KEY::F3), false, false, false};

}

KeyMapper::KeyWrapper KeyMapper::getKeyMapped(const std::string& actionName) {
    // Try to load the default Key mapper file
    if (KeyMapper::mInitialized == false) {
        KeyMapper::loadKeyMapper();
    }

    if (KeyMapper::mKeys.find(actionName) != KeyMapper::mKeys.end()) {
        return KeyMapper::mKeys[actionName];
    } else {
        return KeyMapper::mDefaultKeys[actionName]; 
    }
}

bool KeyMapper::action(const std::string& actionName, Event& evt) {
    KeyMapper::KeyWrapper tmp = {};
    tmp = KeyMapper::getKeyMapped(actionName);

    bool keyCodes = false;

    for(auto it : tmp.keys) {

        if (Keyboard::isKeyPressed(it)) {
            keyCodes = true;
        } else {
            keyCodes = false;
            break;
        }
    }

    return (keyCodes && evt.key.control == tmp.control && evt.key.alt == tmp.alt && evt.key.shift == tmp.shift && evt.key.system == tmp.system);
}

Keyboard::KEY KeyMapper::stringToKey(const std::string& keyName) {
    std::string key = keyName;

    std::transform(key.begin(), key.end(), key.begin(), ::tolower);

    if (key == "a") {
        return Keyboard::KEY::A;
    }

    if (key == "b") {
        return Keyboard::KEY::B;
    }

    if (key == "c") {
        return Keyboard::KEY::C;
    }

    if (key == "d") {
        return Keyboard::KEY::D;
    }

    if (key == "e") {
        return Keyboard::KEY::E;
    }

    if (key == "f") {
        return Keyboard::KEY::F;
    }

    if (key == "g") {
        return Keyboard::KEY::G;
    }

    if (key == "h") {
        return Keyboard::KEY::H;
    }

    if (key == "i") {
        return Keyboard::KEY::I;
    }

    if (key == "j") {
        return Keyboard::KEY::J;
    }

    if (key == "k") {
        return Keyboard::KEY::K;
    }

    if (key == "l") {
        return Keyboard::KEY::L;
    }

    if (key == "m") {
        return Keyboard::KEY::M;
    }

    if (key == "n") {
        return Keyboard::KEY::N;
    }

    if (key == "o") {
        return Keyboard::KEY::O;
    }

    if (key == "p") {
        return Keyboard::KEY::P;
    }

    if (key == "q") {
        return Keyboard::KEY::Q;
    }

    if (key == "r") {
        return Keyboard::KEY::R;
    }

    if (key == "s") {
        return Keyboard::KEY::S;
    }

    if (key == "t") {
        return Keyboard::KEY::T;
    }

    if (key == "u") {
        return Keyboard::KEY::U;
    }

    if (key == "w") {
        return Keyboard::KEY::W;
    }

    if (key == "x") {
        return Keyboard::KEY::X;
    }

    if (key == "v") {
        return Keyboard::KEY::V;
    }

    if (key == "y") {
        return Keyboard::KEY::Y;
    }

    if (key == "z") {
        return Keyboard::KEY::Z;
    }

    if (key == "num0") {
        return Keyboard::KEY::Num0;
    }

    if (key == "num1") {
        return Keyboard::KEY::Num1;
    }

    if (key == "num2") {
        return Keyboard::KEY::Num2;
    }

    if (key == "num3") {
        return Keyboard::KEY::Num3;
    }

    if (key == "num4") {
        return Keyboard::KEY::Num4;
    }

    if (key == "num5") {
        return Keyboard::KEY::Num5;
    }

    if (key == "num6") {
        return Keyboard::KEY::Num6;
    }

    if (key == "num7") {
        return Keyboard::KEY::Num7;
    }

    if (key == "num8") {
        return Keyboard::KEY::Num8;
    }

    if (key == "num9") {
        return Keyboard::KEY::Num9;
    }

    if (key == "escape") {
        return Keyboard::KEY::Escape;
    }

    if (key == "lcontrol") {
        return Keyboard::KEY::LControl;
    }

    if (key == "lshift") {
        return Keyboard::KEY::LShift;
    }

    if (key == "lalt") {
        return Keyboard::KEY::LAlt;
    }

    if (key == "lsystem") {
        return Keyboard::KEY::LSystem;
    }

    if (key == "rcontrol") {
        return Keyboard::KEY::RControl;
    }

    if (key == "rshift") {
        return Keyboard::KEY::RShift;
    }

    if (key == "ralt") {
        return Keyboard::KEY::RAlt;
    }

    if (key == "rsystem") {
        return Keyboard::KEY::RSystem;
    }

    if (key == "menu") {
        return Keyboard::KEY::Menu;
    }

    if (key == "lbracket") {
        return Keyboard::KEY::LBracket;
    }

    if (key == "rbracket") {
        return Keyboard::KEY::RBracket;
    }

    if (key == "semicolon") {
        return Keyboard::KEY::SemiColon;
    }

    if (key == "comma") {
        return Keyboard::KEY::Comma;
    }

    if (key == "period") {
        return Keyboard::KEY::Period;
    }

    if (key == "quote") {
        return Keyboard::KEY::Quote;
    }

    if (key == "slash") {
        return Keyboard::KEY::Slash;
    }

    if (key == "backslash") {
        return Keyboard::KEY::BackSlash;
    }

    if (key == "tilde") {
        return Keyboard::KEY::Tilde;
    }

    if (key == "equal") {
        return Keyboard::KEY::Equal;
    }

    if (key == "dash") {
        return Keyboard::KEY::Dash;
    }

    if (key == "space") {
        return Keyboard::KEY::Space;
    }

    if (key == "return") {
        return Keyboard::KEY::Return;
    }

    if (key == "backspace") {
        return Keyboard::KEY::BackSpace;
    }

    if (key == "tab") {
        return Keyboard::KEY::Tab;
    }

    if (key == "pageup") {
        return Keyboard::KEY::PageUp;
    }

    if (key == "pagedown") {
        return Keyboard::KEY::PageDown;
    }

    if (key == "end") {
        return Keyboard::KEY::End;
    }

    if (key == "home") {
        return Keyboard::KEY::Home;
    }

    if (key == "insert") {
        return Keyboard::KEY::Insert;
    }

    if (key == "delete") {
        return Keyboard::KEY::Delete;
    }

    if (key == "add") {
        return Keyboard::KEY::Add;
    }

    if (key == "subtract") {
        return Keyboard::KEY::Subtract;
    }

    if (key == "multiply") {
        return Keyboard::KEY::Multiply;
    }

    if (key == "divide") {
        return Keyboard::KEY::Divide;
    }

    if (key == "left") {
        return Keyboard::KEY::Left;
    }

    if (key == "right") {
        return Keyboard::KEY::Right;
    }

    if (key == "up") {
        return Keyboard::KEY::Up;
    }

    if (key == "down") {
        return Keyboard::KEY::Down;
    }

    if (key == "numpad0") {
        return Keyboard::KEY::Numpad0;
    }

    if (key == "numpad1") {
        return Keyboard::KEY::Numpad1;
    }

    if (key == "numpad2") {
        return Keyboard::KEY::Numpad2;
    }

    if (key == "numpad3") {
        return Keyboard::KEY::Numpad3;
    }

    if (key == "numpad4") {
        return Keyboard::KEY::Numpad4;
    }

    if (key == "numpad5") {
        return Keyboard::KEY::Numpad5;
    }

    if (key == "numpad6") {
        return Keyboard::KEY::Numpad6;
    }

    if (key == "numpad7") {
        return Keyboard::KEY::Numpad7;
    }

    if (key == "numpad8") {
        return Keyboard::KEY::Numpad8;
    }

    if (key == "numpad9") {
        return Keyboard::KEY::Numpad9;
    }

    if (key == "f1") {
        return Keyboard::KEY::F1;
    }

    if (key == "f2") {
        return Keyboard::KEY::F2;
    }

    if (key == "f3") {
        return Keyboard::KEY::F3;
    }

    if (key == "f4") {
        return Keyboard::KEY::F4;
    }

    if (key == "f5") {
        return Keyboard::KEY::F5;
    }

    if (key == "f6") {
        return Keyboard::KEY::F6;
    }

    if (key == "f7") {
        return Keyboard::KEY::F7;
    }

    if (key == "f8") {
        return Keyboard::KEY::F8;
    }

    if (key == "f9") {
        return Keyboard::KEY::F9;
    }

    if (key == "f10") {
        return Keyboard::KEY::F10;
    }

    if (key == "f11") {
        return Keyboard::KEY::F11;
    }

    if (key == "f12") {
        return Keyboard::KEY::F12;
    }

    if (key == "f13") {
        return Keyboard::KEY::F13;
    }

    if (key == "f14") {
        return Keyboard::KEY::F14;
    }

    if (key == "f15") {
        return Keyboard::KEY::F15;
    }

    if (key == "pause") {
        return Keyboard::KEY::Pause;
    }

    return Keyboard::KEY::Unknown;
}
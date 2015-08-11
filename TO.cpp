#include "TO.h"


int TO::str_to_int(const std::string &str) {
    std::stringstream ss(str);
    int t;
    ss >> t;
    return t;
}

bool TO::str_to_bool(const std::string &str) {
    std::string tmp = str;
    std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);

    bool ret;
    std::istringstream(tmp) >> std::boolalpha >> ret;
    return ret;
}

float TO::str_to_float(const std::string &str) {
    std::stringstream ss(str);
    float t;
    ss >> t;
    return t;
}

double TO::str_to_double(const std::string &str) {
    std::stringstream ss(str);
    double t;
    ss >> t;
    return t;
}

int TO::float_to_int(const float &f) {
    return (int)f;
}

double TO::float_to_double(const float &f) {
    return (double)f;
}

std::string TO::float_to_string(const float &f) {
    char t[200];
    std::sprintf(t,"%f",f);
    return std::string(t);
}

int TO::double_to_int(const double &d) {
    return  (int)d;
}

float TO::double_to_float(const double &d) {
    return (float)d;
}

std::string TO::double_to_str(const double &d) {
    char t[200];
    std::sprintf(t,"%f",d);
    return std::string(t);
}

int TO::bool_to_int(const bool &b) {
    return b;
}

std::string TO::bool_to_str(const bool &b) {
    if (b == true) {
        return "true";
    } else {
        return "false";
    }
}

std::string TO::int_to_str(const int &i) {
    char t[200];
    std::sprintf(t,"%d",i);
    return std::string(t);
}


ME::KEY TO::str_to_KEY(const std::string &key){
    ME::KEY k;

    if ( key == "A") k = ME::A;
    if ( key == "B") k = ME::B;
    if ( key == "C") k = ME::C;
    if ( key == "D") k = ME::D;
    if ( key == "E") k = ME::E;
    if ( key == "F") k = ME::F;
    if ( key == "G") k = ME::G;
    if ( key == "H") k = ME::H;
    if ( key == "I") k = ME::I;
    if ( key == "J") k = ME::J;
    if ( key == "K") k = ME::K;
    if ( key == "L") k = ME::L;
    if ( key == "M") k = ME::M;
    if ( key == "N") k = ME::N;
    if ( key == "O") k = ME::O;
    if ( key == "P") k = ME::P;
    if ( key == "Q") k = ME::Q;
    if ( key == "R") k = ME::R;
    if ( key == "S") k = ME::S;
    if ( key == "T") k = ME::T;
    if ( key == "U") k = ME::U;
    if ( key == "V") k = ME::V;
    if ( key == "W") k = ME::W;
    if ( key == "X") k = ME::X;
    if ( key == "Y") k = ME::Y;
    if ( key == "Z") k = ME::Z;
    if ( key == "Num0") k = ME::Num0;
    if ( key == "Num1") k = ME::Num1;
    if ( key == "Num2") k = ME::Num2;
    if ( key == "Num3") k = ME::Num3;
    if ( key == "Num4") k = ME::Num4;
    if ( key == "Num5") k = ME::Num5;
    if ( key == "Num6") k = ME::Num6;
    if ( key == "Num7") k = ME::Num7;
    if ( key == "Num8") k = ME::Num8;
    if ( key == "Num9") k = ME::Num9;
    if ( key == "Escape") k = ME::Escape;
    if ( key == "LControl") k = ME::LControl;
    if ( key == "LShift") k = ME::LShift;
    if ( key == "LAlt") k = ME::LAlt;
    if ( key == "LSystem") k = ME::LSystem;
    if ( key == "RControl") k = ME::RControl;
    if ( key == "RShift") k = ME::RShift;
    if ( key == "RAlt") k = ME::RAlt;
    if ( key == "RSystem") k = ME::RSystem;
    if ( key == "Menu") k = ME::Menu;
    if ( key == "LBracket") k = ME::LBracket;
    if ( key == "RBracket") k = ME::RBracket;
    if ( key == "SemiColon") k = ME::SemiColon;
    if ( key == "Comma") k = ME::Comma;
    if ( key == "Period") k = ME::Period;
    if ( key == "Quote") k = ME::Quote;
    if ( key == "Slash") k = ME::Slash;
    if ( key == "BackSlash") k = ME::BackSlash;
    if ( key == "Tilde") k = ME::Tilde;
    if ( key == "Equal") k = ME::Equal;
    if ( key == "Dash") k = ME::Dash;
    if ( key == "Space") k = ME::Space;
    if ( key == "Return") k = ME::Return;
    if ( key == "BackSpace") k = ME::BackSpace;
    if ( key == "Tab") k = ME::Tab;
    if ( key == "PageUp") k = ME::PageUp;
    if ( key == "PageDown") k = ME::PageDown;
    if ( key == "End") k = ME::End;
    if ( key == "Home") k = ME::Home;
    if ( key == "Insert") k = ME::Insert;
    if ( key == "Delete") k = ME::Delete;
    if ( key == "Add") k = ME::Add;
    if ( key == "Subtract") k = ME::Subtract;
    if ( key == "Multiply") k = ME::Multiply;
    if ( key == "Divide") k = ME::Divide;
    if ( key == "Left") k = ME::Left;
    if ( key == "Right") k = ME::Right;
    if ( key == "Up") k = ME::Up;
    if ( key == "Down") k = ME::Down;
    if ( key == "Numpad0") k = ME::Numpad0;
    if ( key == "Numpad1") k = ME::Numpad1;
    if ( key == "Numpad2") k = ME::Numpad2;
    if ( key == "Numpad3") k = ME::Numpad3;
    if ( key == "Numpad4") k = ME::Numpad4;
    if ( key == "Numpad5") k = ME::Numpad5;
    if ( key == "Numpad6") k = ME::Numpad6;
    if ( key == "Numpad7") k = ME::Numpad7;
    if ( key == "Numpad8") k = ME::Numpad8;
    if ( key == "Numpad9") k = ME::Numpad9;
    if ( key == "F1") k = ME::F1;
    if ( key == "F2") k = ME::F2;
    if ( key == "F3") k = ME::F3;
    if ( key == "F4") k = ME::F4;
    if ( key == "F5") k = ME::F5;
    if ( key == "F6") k = ME::F6;
    if ( key == "F7") k = ME::F7;
    if ( key == "F8") k = ME::F8;
    if ( key == "F9") k = ME::F9;
    if ( key == "F10") k = ME::F10;
    if ( key == "F11") k = ME::F11;
    if ( key == "F12") k = ME::F12;
    if ( key == "F13") k = ME::F13;
    if ( key == "F14") k = ME::F14;
    if ( key == "F15") k = ME::F15;
    if ( key == "Pause") k = ME::Pause;

    return k;
}

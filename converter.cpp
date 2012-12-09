#include "Converter.h"

using namespace ME;

int Converter::str_to_int(const std::string &str){
    std::stringstream ss(str);
    int t;
    ss >> t;
    return t;
}
bool Converter::str_to_bool(const std::string &str){
    if ( str == "true")
        return true;
    else
        return false;
}
float Converter::str_to_float(const std::string &str){
    std::stringstream ss(str);
    float t;
    ss >> t;
    return t;
}
double Converter::str_to_double(const std::string &str){
    std::stringstream ss(str);
    double t;
    ss >> t;
    return t;
}
char* Converter::str_to_charPoiter(const std::string &str){
    std::stringstream ss(str);
    char *t;
    ss >> t;
    return t;
}

int Converter::float_to_int(const float &f){
    return (int)f;
}
double Converter::float_to_double(const float &f){
    return (double)f;
}
std::string Converter::float_to_string(const float &f){
    char t[200];
    std::sprintf(t,"%f",f);
    return std::string(t);
}

int Converter::double_to_int(const double &d){
    return  (int)d;
}
float Converter::double_to_float(const double &d){
    return (float)d;
}
std::string Converter::double_to_str(const double &d){
    char t[200];
    std::sprintf(t,"%f",d);
    return std::string(t);
}

int Converter::bool_to_int(const bool &b){
    return b;
}
std::string Converter::bool_to_str(const bool &b){
    if ( b == true )
        return "true";
    else
        return "false";
}
std::string Converter::int_to_str(const int &i){
    char t[200];
    std::sprintf(t,"%d",i);
    return std::string(t);
}

Key Converter::str_to_key(const std::string &key){
    ME::Key k;


    if ( key == "A") k = A;
    if ( key == "B") k = B;
    if ( key == "C") k = C;
    if ( key == "D") k = D;
    if ( key == "E") k = E;
    if ( key == "F") k = F;
    if ( key == "G") k = G;
    if ( key == "H") k = H;
    if ( key == "I") k = I;
    if ( key == "J") k = J;
    if ( key == "K") k = K;
    if ( key == "L") k = L;
    if ( key == "M") k = M;
    if ( key == "N") k = N;
    if ( key == "O") k = O;
    if ( key == "P") k = P;
    if ( key == "Q") k = Q;
    if ( key == "R") k = R;
    if ( key == "S") k = S;
    if ( key == "T") k = T;
    if ( key == "U") k = U;
    if ( key == "V") k = V;
    if ( key == "W") k = W;
    if ( key == "X") k = X;
    if ( key == "Y") k = Y;
    if ( key == "Z") k = Z;
    if ( key == "Num0") k = Num0;
    if ( key == "Num1") k = Num1;
    if ( key == "Num2") k = Num2;
    if ( key == "Num3") k = Num3;
    if ( key == "Num4") k = Num4;
    if ( key == "Num5") k = Num5;
    if ( key == "Num6") k = Num6;
    if ( key == "Num7") k = Num7;
    if ( key == "Num8") k = Num8;
    if ( key == "Num9") k = Num9;
    if ( key == "Escape") k = Escape;
    if ( key == "LControl") k = LControl;
    if ( key == "LShift") k = LShift;
    if ( key == "LAlt") k = LAlt;
    if ( key == "LSystem") k = LSystem;
    if ( key == "RControl") k = RControl;
    if ( key == "RShift") k = RShift;
    if ( key == "RAlt") k = RAlt;
    if ( key == "RSystem") k = RSystem;
    if ( key == "Menu") k = Menu;
    if ( key == "LBracket") k = LBracket;
    if ( key == "RBracket") k = RBracket;
    if ( key == "SemiColon") k = SemiColon;
    if ( key == "Comma") k = Comma;
    if ( key == "Period") k = Period;
    if ( key == "Quote") k = Quote;
    if ( key == "Slash") k = Slash;
    if ( key == "BackSlash") k = BackSlash;
    if ( key == "Tilde") k = Tilde;
    if ( key == "Equal") k = Equal;
    if ( key == "Dash") k = Dash;
    if ( key == "Space") k = Space;
    if ( key == "Return") k = Return;
    if ( key == "BackSpace") k = BackSpace;
    if ( key == "Tab") k = Tab;
    if ( key == "PageUp") k = PageUp;
    if ( key == "PageDown") k = PageDown;
    if ( key == "End") k = End;
    if ( key == "Home") k = Home;
    if ( key == "Insert") k = Insert;
    if ( key == "Delete") k = Delete;
    if ( key == "Add") k = Add;
    if ( key == "Subtract") k = Subtract;
    if ( key == "Multiply") k = Multiply;
    if ( key == "Divide") k = Divide;
    if ( key == "Left") k = Left;
    if ( key == "Right") k = Right;
    if ( key == "Up") k = Up;
    if ( key == "Down") k = Down;
    if ( key == "Numpad0") k = Numpad0;
    if ( key == "Numpad1") k = Numpad1;
    if ( key == "Numpad2") k = Numpad2;
    if ( key == "Numpad3") k = Numpad3;
    if ( key == "Numpad4") k = Numpad4;
    if ( key == "Numpad5") k = Numpad5;
    if ( key == "Numpad6") k = Numpad6;
    if ( key == "Numpad7") k = Numpad7;
    if ( key == "Numpad8") k = Numpad8;
    if ( key == "Numpad9") k = Numpad9;
    if ( key == "F1") k = F1;
    if ( key == "F2") k = F2;
    if ( key == "F3") k = F3;
    if ( key == "F4") k = F4;
    if ( key == "F5") k = F5;
    if ( key == "F6") k = F6;
    if ( key == "F7") k = F7;
    if ( key == "F8") k = F8;
    if ( key == "F9") k = F9;
    if ( key == "F10") k = F10;
    if ( key == "F11") k = F11;
    if ( key == "F12") k = F12;
    if ( key == "F13") k = F13;
    if ( key == "F14") k = F14;
    if ( key == "F15") k = F15;
    if ( key == "Pause") k = Pause;

    return k;
}


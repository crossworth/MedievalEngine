#ifndef KIT_H
#define KIT_H
#include <typeinfo>
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>


namespace ME{

class Kit {
public:
    static int str_int(const std::string& str);
    static bool str_bool(const std::string& str);
    static float str_float(const std::string& str);
    static double str_double(const std::string& str);
    static std::wstring str_wstr(const std::string& str);
    static std::string wstr_str(const std::wstring& str);

    static int float_int(const float& f);
    static double float_double(const float& f);
    static std::string float_string(const float& f);

    static int double_int(const double& b);
    static float double_float(const double& b);
    static std::string double_str(const double& b);

    static int bool_int(const bool& b);
    static std::string bool_str(const bool& b);

    static std::string int_str(const int& i);
    static bool int_bool(const bool& b);

};

}

#endif

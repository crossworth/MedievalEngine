#ifndef TO_H
#define TO_H
#include <typeinfo>
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>
#include "key.h"

class TO {
public:
    static int str_to_int(const std::string &str);
    static bool str_to_bool(const std::string &str);
    static float str_to_float(const std::string &str);
    static double str_to_double(const std::string &str);
    static ME::KEY str_to_KEY(const std::string &str);

    static int float_to_int(const float &f);
    static double float_to_double(const float &f);
    static std::string float_to_string(const float &f);

    static int double_to_int(const double &b);
    static float double_to_float(const double &b);
    static std::string double_to_str(const double &b);

    static int bool_to_int(const bool &b);
    static std::string bool_to_str(const bool &b);

    static std::string int_to_str(const int &i);
    static bool int_to_bool(const bool &b);
};

#endif

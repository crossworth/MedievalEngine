#include "Data2.h"

using namespace ME;

int Data2::str_to_int(const std::string &str) {
    std::stringstream ss(str);
    int t;
    ss >> t;
    return t;
}

bool Data2::str_to_bool(const std::string &str) {
    std::string tmp = str;
    std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);

    bool ret;
    std::istringstream(tmp) >> std::boolalpha >> ret;
    return ret;
}

float Data2::str_to_float(const std::string &str) {
    std::stringstream ss(str);
    float t;
    ss >> t;
    return t;
}

double Data2::str_to_double(const std::string &str) {
    std::stringstream ss(str);
    double t;
    ss >> t;
    return t;
}

int Data2::float_to_int(const float &f) {
    return (int)f;
}

double Data2::float_to_double(const float &f) {
    return (double)f;
}

std::string Data2::float_to_string(const float &f) {
    char t[200];
    std::sprintf(t,"%f",f);
    return std::string(t);
}

int Data2::double_to_int(const double &d) {
    return  (int)d;
}

float Data2::double_to_float(const double &d) {
    return (float)d;
}

std::string Data2::double_to_str(const double &d) {
    char t[200];
    std::sprintf(t,"%f",d);
    return std::string(t);
}

int Data2::bool_to_int(const bool &b) {
    return b;
}

std::string Data2::bool_to_str(const bool &b) {
    if ( b == true )
        return "true";
    else
        return "false";
}

std::string Data2::int_to_str(const int &i) {
    char t[200];
    std::sprintf(t,"%d",i);
    return std::string(t);
}

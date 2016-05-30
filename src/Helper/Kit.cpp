#include "Kit.h"

using namespace ME;

int Kit::str_int(const std::string& str) {
    std::stringstream ss(str);
    int t;
    ss >> t;
    return t;
}

int Kit::string_int(const String& str) {
    return Kit::str_int(str.getString());
}

bool Kit::str_bool(const std::string& str) {
    std::string tmp = str;
    std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);

    bool ret;
    std::istringstream(tmp) >> std::boolalpha >> ret;
    return ret;
}

bool Kit::string_bool(const String& str) {
    return Kit::str_bool(str.getString());
}

float Kit::str_float(const std::string& str) {
    std::stringstream ss(str);
    float t;
    ss >> t;
    return t;
}

float Kit::string_float(const String& str) {
    return Kit::str_float(str.getString());
}

double Kit::str_double(const std::string& str) {
    std::stringstream ss(str);
    double t;
    ss >> t;
    return t;
}

double Kit::string_double(const String& str) {
    return Kit::str_double(str.getString());
}

std::wstring Kit::str_wstr(const std::string& str) {
    std::wstringstream ret;
    ret << str.c_str();
    return ret.str();
}

std::string Kit::wstr_str(const std::wstring& str) {
    return std::string(str.begin(), str.end());
}

int Kit::float_int(const float& f) {
    return static_cast<int>(f);
}

double Kit::float_double(const float& f) {
    return static_cast<double>(f);
}

std::string Kit::float_str(const float& f) {
    char t[200];
    std::sprintf(t,"%f",f);
    return std::string(t);
}

int Kit::double_int(const double& d) {
    return static_cast<int>(d);
}

float Kit::double_float(const double& d) {
    return static_cast<float>(d);
}

std::string Kit::double_str(const double& d) {
    char t[200];
    std::sprintf(t,"%f",d);
    return std::string(t);
}

int Kit::bool_int(const bool& b) {
    return b;
}

std::string Kit::bool_str(const bool& b) {
    if (b == true) {
        return "true";
    } else {
        return "false";
    }
}

std::string Kit::int_str(const int& i) {
    char t[200];
    std::sprintf(t,"%d",i);
    return std::string(t);
}

std::vector<std::string> Kit::explode(std::string const& s, char delim) {
    std::vector<std::string> result;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delim); ) {
        result.push_back(std::move(token));
    }

    return result;
}
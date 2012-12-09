#ifndef CONVETER_H
#define CONVETER_H
#include "engine_config.h"
#include "debugger.h"
#include <typeinfo>

namespace ME{

class Converter
{
public:
    static int str_to_int(const std::string &str);
    static bool str_to_bool(const std::string &str);
    static float str_to_float(const std::string &str);
    static double str_to_double(const std::string &str);
    static char* str_to_charPoiter(const std::string &str);

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

    //special types
    static Key str_to_key(const std::string &key);

    // converter Anythig to string
    template <typename T>
    static std::string T_to_string(T const &val){
        std::ostringstream ostr;
        ostr << val;
        return std::string (ostr.str());
    }
    // string to T
    template <typename T>
    static T string_to_T(std::string const &val){
        std::istringstream ss(val);
        T returnValue;


        if ( !(ss >> returnValue) ){
           Debugger *dbg;
           dbg = Debugger::getInstance();
           dbg->log(CRITICAL ,1,("Could not converter " + val + " to " + typeid(ss).name()).c_str());

        }
        return returnValue;

    }



    // converter string to string
    static std::string string_to_T(std::string const &val){
        return val;
    }

};

}

#endif // converter_H

#ifndef CFGPARSER_H
#define CFGPARSER_H
#include "debugger.h"
#include "converter.h"
#include "engine_config.h"


namespace ME{

class CFGParser
{
public:
    CFGParser();
    CFGParser(const std::string &configFile);
    void readFile(const std::string &configFile);
    bool add(std::string key,std::string value);
    void saveFile(const std::string &configFile);

    template <typename T>
    T getKey(std::string key);
    bool keyExists(std::string &key);
    void clear();

private:
    std::string fileName;
    Debugger *dbg;
    std::map<std::string,std::string> contents;
    bool validateLine(std::string &line);
    std::string mGetKey(std::string line);
    std::string mGetValue(std::string line);


};

template <typename T>
T CFGParser::getKey(std::string key){
    std::map<std::string,std::string>::iterator it= contents.find(key);
    if ( it == contents.end()){
        dbg->log(CRITICAL,1,"Cfg file not open!");
    }

    if ( keyExists(key) ){

        T returnValue = Converter::string_to_T<T>(contents[key]);
        return returnValue;
    }else{
        dbg->log(CRITICAL,1,("Key " + key + " not exits in the Config file " + fileName).c_str());
        return T();
    }
}


}


#endif // CFGPARSER_H

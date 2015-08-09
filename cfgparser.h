#ifndef CFGPARSER_H
#define CFGPARSER_H
#include "debugger.h"
#include "TO.h"
#include "config.h"


namespace ME {

class CFGParser {
public:
    CFGParser();
    CFGParser(const std::string &configFile);
    void readFile(const std::string &configFile);
    bool add(std::string key, std::string value);
    void saveFile(const std::string &configFile);

    std::string getKey(std::string key);
    bool keyExists(std::string &key);
    void clear();

private:
    std::string fileName;
    Debugger *dbg;
    std::map<std::string, std::string> contents;
    bool validateLine(std::string &line);
    std::string mGetKey(std::string line);
    std::string mGetValue(std::string line);

};

}


#endif // CFGPARSER_H

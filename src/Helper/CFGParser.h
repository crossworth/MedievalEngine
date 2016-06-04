#ifndef CFGPARSER_H
#define CFGPARSER_H
#include <algorithm>
#include "LogInc.h"



namespace ME {

class CFGParser {
public:
    CFGParser();
    CFGParser(const std::string& configFile);
    bool readFile(const std::string& configFile);
    bool add(std::string key, String value);
    void save();
    void saveFile(const std::string& configFile);

    String getKey(std::string key);
    bool keyExists(std::string& key);
    void clear();

    std::map<std::string, String> getContents();
private:
    std::string mFileName;
    std::map<std::string, String> mContents;
    bool validateLine(std::string& line);
    std::string mGetKey(std::string line);
    String mGetValue(std::string line);

};

}


#endif // CFGPARSER_H

#ifndef MEDIEVALENGINE_HELPER_CFGPARSER_H_
#define MEDIEVALENGINE_HELPER_CFGPARSER_H_
#include <algorithm>
#include <map>

#include "LogInc.h"

namespace ME {

class CFGParser {
public:
    CFGParser();
    CFGParser(const std::string &configFile);
    bool readFile(const std::string &configFile);
    bool add(std::string key, String value);
    void save();
    void saveFile(const std::string &configFile);

    String getKey(std::string key);
    bool keyExists(std::string &key);
    void clear();

    std::map<std::string, String> getContents();
private:
    std::string mFileName;
    std::map<std::string, String> mContents;
    bool validateLine(std::string &line);
    std::string mGetKey(std::string line);
    String mGetValue(std::string line);

};

}


#endif // MEDIEVALENGINE_HELPER_CFGPARSER_H_

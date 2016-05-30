#ifndef STRINGS_H
#define STRINGS_H
#include "Helper/String.h"
#include "Helper/CFGParser.h"
#include "Helper/Random.h"


namespace ME {

class Strings {
public:
    static bool openLanguageFile(const std::string& languageFile);
    static String get(const std::string& name);
    static String getItemArrayRandom(const std::string& name);
private:
    Strings();
    static std::map<std::string, String> mStrings;
};

}

#endif // STRINGS_H

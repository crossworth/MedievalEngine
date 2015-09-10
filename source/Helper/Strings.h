#ifndef STRINGS_H
#define STRINGS_H
#include <SFML/System/String.hpp>
#include "Helper/CFGParser.h"
#include "Helper/Random.h"


namespace ME {

class Strings {
public:
    static bool openLanguageFile(const std::string& lenguageFile);
    static sf::String get(const std::string& name);
    static sf::String getItemArrayRandom(const std::string& name);
private:
    Strings();
    static std::map<std::string, std::string> mStrings;
};

}

#endif // STRINGS_H

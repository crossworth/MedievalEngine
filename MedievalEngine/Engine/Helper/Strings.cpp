#include "Strings.h"


using namespace ME;

Strings::Strings() {

}

std::map<std::string, std::string> Strings::mStrings;

bool Strings::openLanguageFile(const std::string& lenguageFile) {
    CFGParser language(lenguageFile);
    std::map<std::string, std::string> data;

    data = language.getContents();
    Strings::mStrings.clear();

    for(auto it = data.begin(); it != data.end(); it++) {
        Strings::mStrings[(*it).first] = sf::String((*it).second);
    }

    language.clear();

    if (Strings::mStrings.size() > 0) {
        return true;
    } else {
        return false;
    }
}

sf::String Strings::get(const std::string& name) {
    if (Strings::mStrings.find(name) != Strings::mStrings.end()) {
        return Strings::mStrings[name];
    } else {
        return sf::String(name);
    }
}

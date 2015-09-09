#include "Strings.h"


using namespace ME;

Strings::Strings() {

}

std::map<std::string, std::string> Strings::mStrings;

bool Strings::openLanguageFile(const std::string& lenguageFile) {
    CFGParser language(lenguageFile);
    std::map<std::string, std::string> data;

    data = language.getContents();

    // Clear all the String's since we just opened another it
    // file that contains it
    Strings::mStrings.clear();

    // TODO(Pedro): Do we need to interate end all the time?
    for(auto it = data.begin(); it != data.end(); it++) {
        Strings::mStrings[(*it).first] = sf::String((*it).second);
    }

    // we dont need to clear this since it's going alt of scope
    // but we do anyway
    language.clear();

    // if we have found any string we are good
    if (Strings::mStrings.size() > 0) {
        return true;
    } else {
        // else we just return false
        return false;
    }
}

sf::String Strings::get(const std::string& name) {
    // if we found a string we just return it
    // else we return the name requested
    //
    // String::get("not_found_str") will return "not_found_str"
    if (Strings::mStrings.find(name) != Strings::mStrings.end()) {
        return Strings::mStrings[name];
    } else {
        return sf::String(name);
    }
}

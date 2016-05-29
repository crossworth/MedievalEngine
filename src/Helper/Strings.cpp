#include "Strings.h"


using namespace ME;

Strings::Strings() {

}

std::map<std::string, std::string> Strings::mStrings;

bool Strings::openLanguageFile(const std::string& languageFile) {
    std::cout << "Tring to open file " << languageFile << std::endl;
    CFGParser language(languageFile);
    std::map<std::string, std::string> data;

    data = language.getContents();

    // Clear all the String's since we just opened another it
    // file that contains it
    Strings::mStrings.clear();

    // TODO(Pedro): Do we need to interate end all the time?
    for(auto it = data.begin(); it != data.end(); it++) {
        Strings::mStrings[(*it).first] = sf::String((*it).second);
    }

    // we dont need to clear this since it's going out of scope
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

sf::String Strings::getItemArrayRandom(const std::string& name) {
    // append the prefixe _ar_
    std::string nameTmp = name + "_ar_";
    // our counter variable
    MEInt64 max = 0;

    // loop through all the itens 
    for(auto it = Strings::mStrings.begin(); it != Strings::mStrings.end(); it++) {
        // if it's contain our name we increment the array
        if (it->first.find(nameTmp) != sf::String::InvalidPos) {
            max++;
        }
    }

    // Remove one number just to be on bounds of the array
    if (max > 0) {
        max--;
    }

    // generate the final name with the random number
    // NOTE(Pedro): This could call NAME_ar_0 which may be undefined
    // so we just return a string with the name
    nameTmp = nameTmp + std::to_string(Random::get(max));

    if (Strings::mStrings.find(nameTmp) != Strings::mStrings.end()) {
        return Strings::mStrings[nameTmp];
    } else {
        return sf::String(nameTmp);
    }
}
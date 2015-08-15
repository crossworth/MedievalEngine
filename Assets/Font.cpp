#include "Font.h"

using namespace ME;

Font::Font(const std::string &fileName) {
    mType = "font";
    loadFromFile(fileName);
}

sf::Font* Font::loadFromFile(const std::string &fileName){
    if (!mFont.loadFromFile(ENGINE_DEFAULTS::ASSETS_PATH + fileName)) {
        LOG << ("[Font::loadFromFile] Error while opening font: " + ENGINE_DEFAULTS::ASSETS_PATH + fileName).c_str() << std::endl;
    }
    return &mFont;
}

sf::Font* Font::getResourcePointer() {
    return &mFont;
}

#include "Font.h"

using namespace ME;

AssetID Font::DEFAULT_FONT = 0;

Font::Font() {
    mType = "font";
}

Font::Font(const std::string &fileName) {
    mType = "font";
    loadFromFile(fileName);
}

sf::Font* Font::loadFromFile(const std::string &fileName){
    if (!mFont.loadFromFile(ENGINE_DEFAULTS::ASSETS_PATH + fileName)) {
        LOG << ("[Font::loadFromFile] Error while opening font: " +
                ENGINE_DEFAULTS::ASSETS_PATH + fileName).c_str() << std::endl;
    }
    return &mFont;
}

sf::Font* Font::loadFromMemory(SM::BYTE* bytes, std::size_t size){
    if (!mFont.loadFromMemory(static_cast<void*>(bytes), size)) {
        LOG << "[Font::loadFromMemory] Error while opening font from memory"
            << std::endl;
    }
    return &mFont;
}

sf::Font* Font::getResourcePointer() {
    return &mFont;
}

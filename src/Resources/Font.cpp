#include "Font.h"

using namespace ME;

std::string Font::Default  = "";
std::string Font::GameFont = "";

Font::Font() {
    mType = Resource::Type::FONT;
}

bool Font::loadFromFile(const std::string &fileName){
    if (!mFont.loadFromFile(ENGINE_DEFAULTS::ASSETS_PATH + fileName)) {
        LOG << Log::WARNING << "[Font::loadFromFile] Error while opening font: "
            << ENGINE_DEFAULTS::ASSETS_PATH + fileName
            << std::endl;
    } else {
        mIsValid = true;
    }

    return mIsValid;
}

bool Font::loadFromMemory(byte *bytes, std::size_t size){
    if (!mFont.loadFromMemory(static_cast<void*>(bytes), size)) {
        LOG << Log::WARNING << "[Font::loadFromMemory] Error while opening font from memory"
            << std::endl;
    } else {
        mIsValid = true;
    }

    return mIsValid;
}

sf::Font* Font::getResourcePointer() {
    return &mFont;
}

float Font::getLineSpacing(const unsigned int &size) const {
    return mFont.getLineSpacing(size);
}

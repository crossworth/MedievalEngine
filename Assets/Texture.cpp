#include "Texture.h"

using namespace ME;

Texture::Texture(const std::string &fileName) {
    mType = "texture";
    loadFromFile(fileName);
}

sf::Texture* Texture::getResourcePointer() {
    return &mTexture;
}

sf::Texture* Texture::loadFromFile(const std::string &fileName) {
    if (!mTexture.loadFromFile(ENGINE_DEFAULTS::ASSETS_PATH + fileName)) {
        LOG << ("[Texture::loadFromFile] Error while opening texture: " + ENGINE_DEFAULTS::ASSETS_PATH + fileName).c_str() << std::endl;
    }
    return &mTexture;
}

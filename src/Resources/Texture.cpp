#include "Texture.h"

using namespace ME;

Texture::Texture(const std::string &fileName) {
    mType = Resource::Type::TEXTURE;
    loadFromFile(fileName);
}

sf::Texture* Texture::getResourcePointer() {
    return &mTexture;
}

sf::Texture* Texture::loadFromFile(const std::string &fileName) {
	mIsValid = true;

    if (!mTexture.loadFromFile(ENGINE_DEFAULTS::DATA_PATH + fileName)) {
        LOG << ("[Texture::loadFromFile] Error while opening texture: " +
                ENGINE_DEFAULTS::DATA_PATH + fileName).c_str() << std::endl;
        mIsValid = false;
    }
    return &mTexture;
}

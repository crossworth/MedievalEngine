#include "AssetsManager.h"

using namespace ME;


AssetsManager* AssetsManager::mInstance = nullptr;

AssetsManager* AssetsManager::getInstance() {
    if (!mInstance) {
        mInstance = new AssetsManager;
    }
    return mInstance;
}

AssetsManager::AssetsManager() {
    LOG << Log::VERBOSE << "[AssetsManager::AssetsManager] AssetsManager created" << std::endl;
}

MEid AssetsManager::loadTexture(const std::string &fileName) {
    MEid textureID     = ID::get();
    mAssets[textureID] = new Texture(fileName);
    return textureID;
}

MEid AssetsManager::createSprite(const MEid &texture) {
    MEid spriteID     = ID::get();
    mAssets[spriteID] = new Sprite();
    static_cast<Sprite*>(mAssets[spriteID])->setTexture(static_cast<Texture*>(getAsset(texture)));
    return spriteID;
}

Asset* AssetsManager::getAsset(const MEid &id) {
    if (mAssets.find(id) != mAssets.end()) {
        return mAssets[id];
    } else {
        return new Asset;
    }
}

AssetsManager::~AssetsManager() {
    LOG << Log::VERBOSE << "[AssetsManager::~AssetsManager] AssetsManager cleaned" << std::endl;
}

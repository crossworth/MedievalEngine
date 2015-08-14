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

AssetsManager::~AssetsManager() {
    LOG << Log::VERBOSE << "[AssetsManager::~AssetsManager] AssetsManager cleaned" << std::endl;
}
